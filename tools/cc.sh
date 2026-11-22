#!/usr/bin/env bash
# Compile one C file the way the original PS2 game was built: an EE GCC
# (Sony's Linux builds, or SN Systems' Windows builds under wibo) followed by
# GNU as for the R5900, or Metrowerks CodeWarrior (mwccps2.exe under wibo),
# which writes the object itself.
# Usage: tools/cc.sh in.c out.o   (or: tools/cc.sh in.c -o out.o)
# Settings come from the environment (dk, make) or else from config.mk:
# DK_GCC (an ee-gcc version, or mwcps2-<version>), DK_CFLAGS, DK_G, DK_WARM.
set -euo pipefail

# A warm build (below) has mwccgap run this script as its compiler, with mwccps2's
# arguments ending in `-o OUT FILE.c`: one mwccps2 run compiles the warm-up file and
# then FILE.c, and only FILE.c's object is kept.
if [ "${1:-}" = "-c" ]; then
    ARGS=("$@")
    N=$#
    DIR="$(mktemp -d)"
    trap 'rm -rf "$DIR"' EXIT
    wibo "${DK_WARM_MWCC:?}" "${ARGS[@]:0:N-2}" "$DIR" "${DK_WARM_FILE:?}" "${ARGS[N-1]}"
    NAME="$(basename "${ARGS[N-1]}")"
    mv "$DIR/${NAME%.*}.o" "${ARGS[N-2]}"
    exit 0
fi

IN="$1"
if [ "${2:-}" = "-o" ]; then OUT="$3"; else OUT="$2"; fi
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
TC="${DK_TOOLCHAIN:?load the toolchain first: . ~/decomp/toolchain/env.sh}"
if [ -z "${DK_GCC:-}" ]; then
    eval "$(sed -n 's/^export \(DK_[A-Z]*\) := \(.*\)$/\1="\2"/p' "$ROOT/config.mk")"
fi
# Files in config/gcc_files.txt (Sony's SDK libraries) were built with an EE GCC, not the
# game's compiler. Each line gives the file, the GCC version, -G and the flags:
# `src/sdk/kernel_glue.c 2.9-991111 0 -O2`. DK_GCC_LIST=0 (dk try --gcc) ignores the list.
GCC_LIST="$ROOT/config/gcc_files.txt"
if [ "${DK_GCC_LIST:-1}" = 1 ] && [ -f "$GCC_LIST" ]; then
    IN_ABS="$(cd "$(dirname "$IN")" && pwd)/$(basename "$IN")"
    ROW="$(awk -v f="${IN_ABS#"$ROOT"/}" '{ sub(/#.*/, "") } $1 == f { $1 = ""; print; exit }' "$GCC_LIST")"
    if [ -n "$ROW" ]; then
        read -r DK_GCC DK_G DK_CFLAGS <<< "$ROW"
    fi
fi
EE="$TC/ee-gcc/$DK_GCC"
PRE="$TC/ee-gcc/2.96"  # a Linux build, used only to preprocess
PRE_LIB="$(dirname "$(find "$PRE/lib" -name cpp0 | head -1)")"
G="${DK_G:-0}"
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

# DK_EXTRA_INCLUDE (from dk try) shadows headers, e.g. a game.h without a guessed
# prototype of the function being tried.
CPP_FLAGS="${DK_EXTRA_INCLUDE:+-I$DK_EXTRA_INCLUDE} -I$ROOT/include -I$ROOT/src"
mkdir -p "$(dirname "$OUT")"
# Dependencies for make come from the system cpp. It is 64-bit, so Metrowerks
# builds also run inside sandboxes that ban 32-bit programs (Codex on Linux).
cpp -M -nostdinc $CPP_FLAGS "$IN" 2>/dev/null | sed "1s|^[^:]*:|$OUT:|" > "$TMP/deps" || true
[ -z "${ROW:-}" ] || echo "$OUT: $GCC_LIST" >> "$TMP/deps"  # taken off the list = compiled again

if [[ "$DK_GCC" == mwcps2-* ]]; then
    # mwccgap swaps each INCLUDE_ASM line for its assembled function. It reads C
    # from stdin whenever stdin isn't a terminal, so stdin must be empty.
    IN_ABS="$(cd "$(dirname "$IN")" && pwd)/$(basename "$IN")"
    OUT_ABS="$(cd "$(dirname "$OUT")" && pwd)/$(basename "$OUT")"
    MW="$TC/mwcps2/${DK_GCC#mwcps2-}/mwccps2.exe"
    [ -f "$MW" ] || MW="${MW%/*}/mwccmips.exe"  # 2.3 (1999) has the older name
    # Warm files: the original game was compiled many files per mwccps2 run. Once the
    # compiler has called a runtime helper with arguments in a0/a1 (double maths or
    # compare, 64-bit divide), every later `(s32)` float cast (jal fptosi) is treated
    # as using a0/a1, in later functions and later files of the same run. A file listed
    # in config/warm_files.txt (path from the project root) is compiled in one run right
    # after a tiny warm-up file that makes such a call. DK_WARM=1 or 0 overrides the
    # list (dk try sets it for a function whose file is listed).
    WARM_LIST="$ROOT/config/warm_files.txt"
    if [ -z "${DK_WARM:-}" ]; then
        DK_WARM=0
        if [ -f "$WARM_LIST" ] && awk -v f="${IN_ABS#"$ROOT"/}" \
                '{ sub(/#.*/, ""); $1 = $1 } $0 == f { hit = 1 } END { exit !hit }' "$WARM_LIST"; then
            DK_WARM=1
        fi
    fi
    # A code module can have its own warm level (config/mod_warm.txt): the module is the file's
    # name under src/mod, or else (a dk try copy) the suffix of the first module function named in it.
    WARM_SRC='double warm(double a, double b) {\n    return a * b;\n}\n'
    MOD_WARM="$ROOT/config/mod_warm.txt"
    if [ "$DK_WARM" = 1 ] && [ -f "$MOD_WARM" ]; then
        MOD="$(basename "$IN_ABS" .c)"
        case "$IN_ABS" in
            "$ROOT"/src/mod/*) ;;
            *) MOD="$(grep -o -m1 -E '\bfunc_[0-9A-F]{8}_[bcm][0-9]{3}\b' "$IN_ABS" | head -1 | sed 's/.*_//' || true)" ;;
        esac
        LEVEL="$(awk -v m="$MOD" '{ sub(/#.*/, "") } $1 == m { print $2 }' "$MOD_WARM")"
        case "$LEVEL" in
            0) DK_WARM=0 ;;
            1) WARM_SRC='double warm(int a) {\n    return a;\n}\n' ;;
        esac
    fi
    COMPILER=(--mwcc-path "$MW" --use-wibo --wibo-path "$(command -v wibo)")
    if [ "$DK_WARM" = 1 ]; then
        printf "$WARM_SRC" > "$TMP/dk_warm.c"
        echo "$OUT: $MOD_WARM" >> "$TMP/deps"
        export DK_WARM_FILE="$TMP/dk_warm.c" DK_WARM_MWCC="$MW"
        COMPILER=(--mwcc-path "$ROOT/tools/cc.sh")
        echo "$OUT: $WARM_LIST" >> "$TMP/deps"  # taken off the list = compiled again
    fi
    (cd "$ROOT" && python3 "$TC/src/mwccgap/mwccgap.py" "$IN_ABS" "$OUT_ABS" "${COMPILER[@]}" \
        --as-path "$(command -v mipsel-none-elf-as)" --as-march r5900 --as-mabi eabi --as-flags "-G$G" \
        --macro-inc-path include/mwccgap.inc \
        -nostdinc -stderr ${DK_EXTRA_INCLUDE:+"-I$DK_EXTRA_INCLUDE"} "-I$ROOT/include" "-I$ROOT/src" $DK_CFLAGS \
        < /dev/null)
    python3 "$ROOT/tools/pad_functions.py" "$OUT_ABS"
    # Switch tables: point them at the game's own tables in the data blob (see there).
    (cd "$ROOT" && python3 tools/jtbl_fix.py "$OUT_ABS")
    mv "$TMP/deps" "$OUT.d"
    exit 0
fi
"$PRE/bin/ee-gcc" -B"$PRE_LIB/" -E $CPP_FLAGS "$IN" -o "$TMP/in.i"
# GCC 2.96 code changes once the headers pass a size: only the prototypes the file uses go in (see there).
python3 "$ROOT/tools/trim_protos.py" "$TMP/in.i"
if [ -x "$EE/bin/ee-gcc" ]; then
    LIB="$(dirname "$(find "$EE/lib" -name cc1 | head -1)")"
    (cd "$TMP" && "$EE/bin/ee-gcc" -B"$LIB/" -S "-G$G" $DK_CFLAGS in.i -o out.s)
else
    (cd "$TMP" && wibo "$EE/bin/ee-gcc.exe" -S "-G$G" $DK_CFLAGS in.i -o out.s)
fi
# Switch tables: GCC's own go to .rdata, which the link drops; load the game's (see there).
(cd "$ROOT" && python3 tools/jtbl_fix.py --gcc "$TMP/out.s")
# Double constants the original loaded from its literal pool (`ld $5,sym`) load from the game's (see there).
(cd "$ROOT" && python3 tools/litpool_fix.py "$TMP/out.s")
# Sony's EE assembler turned GCC's `move` into a 64-bit daddu; binutils 2.45 makes it `or`.
# The C library's assembler (the 2.96 files) never moved that macro into a branch's delay
# slot (`move $2,$4; j $31; nop`, `move $4,$2; jal dptofp; nop`); a plain daddu would be
# moved, so there it is emitted as a noreorder instruction. The SDK libraries' assembler
# (2.9 files) did move it.
if [ "$DK_GCC" = 2.96 ]; then
    sed -i -E 's/^([[:space:]]+)move([[:space:]]+)([^,]+),([^[:space:]#]+)/\1.set\tpush\n\1.set\tnoreorder\n\1daddu\2\3,\4,$0\n\1.set\tpop/' "$TMP/out.s"
else
    sed -i -E 's/^([[:space:]]+)move([[:space:]]+)([^,]+),([^[:space:]#]+)/\1daddu\2\3,\4,$0/' "$TMP/out.s"
fi
# The C library's assembler put a nop after an `mtc1` when the next FPU instruction reads the
# even/odd register PAIR it wrote (old gas compares `reg & ~1`: `mtc1 $at,$f1; nop; mul.s $f0,..`,
# but `mtc1 $at,$f0; mul.s $f2,$f12,$f13` has none); binutils only for the same register. `li.s`
# ends in an mtc1 too (gas expands it). Only in reorder code: GCC handles its own noreorder.
if [ "$DK_GCC" = 2.96 ]; then
    perl -i -ne 'BEGIN { @st = (0); $mt = -1 }
        if (/^\s*\.set\s+push\b/) { push @st, $st[-1] }
        elsif (/^\s*\.set\s+pop\b/) { pop @st }
        elsif (/^\s*\.set\s+noreorder\b/) { $st[-1] = 1 }
        elsif (/^\s*\.set\s+reorder\b/) { $st[-1] = 0 }
        elsif (/^\s+([a-z][a-z0-9.]*)\s+(.*)$/) {
            my ($m, $o) = ($1, $2);
            if ($mt >= 0 && !$st[-1] && $m =~ /^(c\.[a-z]+\.s|[a-z]+\.s|cvt\.[a-z]\.[a-z])$/
                && $m !~ /^(li|l|s)\.s$/) {
                my @r = ($o =~ /\$f(\d+)/g);
                shift @r unless $m =~ /^c\./;
                print "\tnop\n" if grep { ($_ & ~1) == ($mt & ~1) } @r;
            }
            $mt = -1;
            if (!$st[-1]) {
                if ($m eq "mtc1" && $o =~ /,\s*\$f(\d+)/) { $mt = $1 }
                elsif ($m eq "li.s" && $o =~ /^\$f(\d+)/) { $mt = $1 }
            }
        }
        print' "$TMP/out.s"
fi
# The C library's assembler never moved an instruction of an address macro (`l.s $f0,D_X($2)`,
# `lw $2,D_X($3)`, `la`) into the next branch's delay slot (fmodf: `lwc1 $f0,%lo(D_X)($at); b; nop`);
# binutils moves the expansion's last instruction there. A local label before the branch stops it.
# The same for GCC's 64-bit constant `li.d` (expanded below as `dli`: scalbn `dsll32; jal dpmul; nop`).
# It never moved a 64-bit `ld`/`sd` into a delay slot either (every 2.96 function: `ld ..%lo(..)` before a
# branch 10x, always with a nop slot; pow's `sd` before `bnez`), and never filled the slot of a `jal` that GCC left
# to it (GCC's own .set noreorder fills stay): __floatdisf's `dsra32 a0; jal litodp; nop`. Adding both changed no
# 2.96 file's existing code (chatE 16 Oct).
if [ "$DK_GCC" = 2.96 ]; then
    perl -i -ne 'BEGIN { $n = 0; $held = 0 }
        print ".Lnofill", $n++, ":\n" if ($held
            && /^\s+(b|j|jal|jr|jalr|bal|beqz?l?|bnez?l?|b[gl][et]zl?|b[gl]tzall?|bgezall?|bc1[tf]l?)\s/)
            || /^\s+jal\s/;
        $held = 0 if /^\s+[a-z]/;
        $held = 1 if /^\s+(l[bhwd]u?|lq|s[bhwdq]|lwc1|swc1|ldc1|sdc1|l\.[sd]|s\.[sd]|d?la)\s+[^,]+,\s*[A-Za-z_]/;
        $held = 1 if /^\s+li\.d\s/;
        $held = 1 if /^\s+(ld|sd)\s/;
        print' "$TMP/out.s"
fi
# Old gas left a label BEFORE the hazard nop after an `mfc1` (powf: `mfc1 $7,$f0` / `.L: nop` /
# `daddu $3,$7,$0`, a branch lands on the nop); binutils moves the label past the nop. When a label
# sits between `mfc1 $N` and an instruction reading $N, the nop is written after the label.
if [ "$DK_GCC" = 2.96 ]; then
    perl -0777 -i -pe 's/^(\s+mfc1\s+\$(\d+),[^\n]*\n)((?:[\$.\w]+:[^\n]*\n)+)((?:\s+\.set\s[^\n]*\n)*)(\s+([a-z][a-z0-9.]*)\s+([^\n]*))/my ($h, $r, $l, $d, $i, $m, $o) = ($1, $2, $3, $4, $5, $6, $7); my @x = split m{,}, $o; shift @x unless $m =~ m{^(s[bhwdq]|b|j)}; (grep { m{\$$r\b} } @x) ? "$h$l\tnop\n$d$i" : "$h$l$d$i"/gme' "$TMP/out.s"
fi
# Old gas never moved into a branch's delay slot an instruction that directly follows a `.set noreorder`
# block (the slot GCC filled itself); binutils does (sceCdSearchFile: `jal cmd_sem_init; sd` /
# `lw $4,semid; jal PollSema; nop`). The first instruction after such a block is counted, and a branch
# right after it gets a local label, which stops the swap. A label or a `.p2align` in between changes
# nothing: old gas kept its history across both (_sceCd_cd_callback: `b L2; ld` / `L1: lw $4,sem` /
# `jal iSignalSema; nop`; sceTtyWrite's sceDeci2Poll loop; _vfprintf_r: `b; addiu` / `.p2align 3` /
# `$L84: ld $4,504($sp)` / `jal isnan; nop`). All 17 GCC files compile byte-identical otherwise.
perl -i -ne 'BEGIN { $n = 0; $noreo = 0; $after = 0; $count = 0 }
    if (/^\s+\.set\s+noreorder\b/) { $noreo = 1 }
    elsif (/^\s+\.set\s+reorder\b/) { if ($noreo) { $after = 1; $count = 0 } $noreo = 0 }
    elsif (!$noreo && /^\s+([a-z][a-z0-9.]*)(\s|$)/) {
        if ($after && $count == 1
            && /^\s+(b|j|jal|jr|jalr|bal|beqz?l?|bnez?l?|b[gl][et]zl?|b[gl]tzall?|bgezall?|bc1[tf]l?)\s/) {
            print ".Lnoreofill", $n++, ":\n";
        }
        $count++;
        $after = 0 if $count > 1;
    }
    print' "$TMP/out.s"
# binutils refuses cvt.w.s on the r5900 (the EE's rounds toward zero); Sony's assembler took
# it (libm's floor/ceil/modf), so write its word: 0x46000024 | fs << 11 | fd << 6.
perl -pi -e 's/^(\s+)cvt\.w\.s\s+\$f(\d+),\s*\$f(\d+)/sprintf("%s.word 0x%08X", $1, 0x46000024 | ($3 << 11) | ($2 << 6))/e' "$TMP/out.s"
# Sony's assembler put no nop between an inline `mfc0` and an instruction reading its result
# (func_0017C3B0: `mfc0 $2,$12; xori $2,$2,1`); binutils pads it as a coprocessor hazard.
# Written as its word, gas doesn't track it.
perl -pi -e 's/^(\s+)mfc0\s+\$(\d+),\s*\$(\d+)\s*$/sprintf("%s.word 0x%08X", $1, 0x40000000 | ($2 << 16) | ($3 << 11))/e' "$TMP/out.s"
# The same for an inline `cfc2.ni` (a VU0 control register read: libdev, libgraph's sceGsSyncPath):
# Sony's assembler put no nop before the instruction reading its result (sceDevVu0Pause: `cfc2.ni
# $2,$vi28; ori $2,$2,2`); binutils pads it. Written as its word: 0x48400000 | rt << 16 | vi << 11.
perl -pi -e 's/^(\s+)cfc2\.ni\s+\$(\d+),\s*\$vi(\d+)[ 	]*$/sprintf("%s.word 0x%08X", $1, 0x48400000 | ($2 << 16) | ($3 << 11))/e' "$TMP/out.s"
# GCC loads a double constant into a GPR (soft-float doubles) as `li.d $N,<value>`; binutils
# refuses it for the r5900, Sony's assembler expanded it as `dli` does (libgcc2's __floatdidf).
perl -pi -e 's/^(\s+)li\.d\s+\$(\d+),\s*(\S+)\s*$/sprintf("%sdli\t\$%s,0x%016X\n", $1, $2, unpack("Q<", pack("d<", $3)))/e' "$TMP/out.s"
# GCC's divide-by-zero trap is `break 7`; Sony's assembler put the 7 in the low code field
# (0x000001CD, shown as `break 0, 7`), binutils in the high one (0x0007000D).
sed -i -E 's/^([[:space:]]+)break([[:space:]]+)7[[:space:]]*$/\1break\20,7/' "$TMP/out.s"
# The C library's assembler had an early form of Sony's R5900 short-loop fix (it keeps a label before a
# hazard nop, as the 2.10-ee gas's fix does, but otherwise assembles like 2.9-ee-991111). At a backward
# branch it filled itself (reorder mode) it counted the words from the target label to the end of the last
# closed fragment (an alignment closes one; the fragment being filled counted as empty, where 2.10-ee
# counts it), did not look for branches inside the loop, and put 5 - n nops before the branch when n <= 4,
# after GCC's own short-loop nops. The one such branch is __ieee754_pow's `bgez $19` back to `move $2,$0;
# b; ld` (GCC 4 nops + 2 here); every other 2.96 file compiles byte-identical with or without this.
if [ "$DK_GCC" = 2.96 ]; then
    perl -i -ne 'BEGIN { @st = (0); $w = 0; $unk = 0; %lab = (); @al = () }
        my $t = $_; $t =~ s/#.*//;
        my $br = qr/^(b|beqz?l?|bnez?l?|b[gl][et]zl?|bc1[tf]l?)$/;
        if ($t =~ /^\s*\.set\s+push\b/) { push @st, $st[-1] }
        elsif ($t =~ /^\s*\.set\s+pop\b/) { pop @st }
        elsif ($t =~ /^\s*\.set\s+noreorder\b/) { $st[-1] = 1 }
        elsif ($t =~ /^\s*\.set\s+reorder\b/) { $st[-1] = 0 }
        elsif ($t =~ /^\s*\.(p2)?align\b/) { push @al, $w }
        elsif ($t =~ /^([\$.\w]+):/) { $lab{$1} = $w }
        elsif ($t =~ /^\s+(\.word|[a-z][a-z0-9.]*)\s*(.*?)\s*$/) {
            my ($m, $o) = ($1, $2);
            if (!$st[-1] && $m =~ $br && $o =~ /([\$.\w]+)$/ && exists $lab{$1} && $unk <= $lab{$1}) {
                my $L = $lab{$1};
                my @b = grep { $_ > $L && $_ <= $w } @al;
                if (@b && $b[-1] - $L <= 4) {
                    for (1 .. 5 - ($b[-1] - $L)) { print "\t.set\tpush\n\t.set\tnoreorder\n\tnop\n\t.set\tpop\n"; $w++ }
                }
            }
            # words: one per instruction; a branch or jump left to the assembler (its delay slot),
            # a macro (`li.d`, `dli`, `la`, `li`, `li.s`) or a load/store through a symbol: not counted exactly
            my $s = 1; my $u = 0;
            $s = scalar(split(/,/, $o)) if $m eq ".word";
            $u = 1 if $m =~ /^(li\.d|dli|d?la|li|li\.s)$/
                || $m =~ /^(l[bhwdq]u?|s[bhwdq]|l[wd]c1|s[wd]c1|l\.[sd]|s\.[sd])$/ && $o =~ /,\s*[A-Za-z_]/
                || (!$st[-1] && ($m =~ $br || $m =~ /^(j|jal|jr|jalr)$/));
            $w += $s;
            $unk = $w + 1 if $u;
        }
        print' "$TMP/out.s"
fi
# GCC objects were linked 8-byte aligned; the linker script's SUBALIGN(4) is not, so the
# file's last function keeps its padding here. The list's last file ends where Metrowerks
# code starts, on a 16-byte boundary (sdk/lgcc -> game/szgame at 0x1A6C80).
P2=3
if [ -n "$ROW" ] && [ "${IN_ABS#"$ROOT"/}" = "$(awk '{ sub(/#.*/, "") } NF { f = $1 } END { print f }' "$GCC_LIST")" ]; then
    P2=4
fi
printf '\t.text\n\t.p2align %s\n' "$P2" >> "$TMP/out.s"

# Sony's assembler expanded GCC's address macros (`lbu $3,D_X($2)`, `la`) with 32-bit adds
# (`addu`, `addiu`); binutils' eabi64 uses `daddu`/`daddiu`. o64 assembles the same 64-bit
# code with 32-bit addresses; the header's ABI field is then set back to eabi64 for the link.
mipsel-none-elf-as -EL "-G$G" -march=r5900 -mabi=o64 -no-pad-sections \
    -I "$ROOT" -I "$ROOT/include" -o "$OUT" "$TMP/out.s"
perl -e 'open(F, "+<", $ARGV[0]) or die; binmode F; seek(F, 0x24, 0); read(F, $b, 4);
    seek(F, 0x24, 0); print F pack("V", (unpack("V", $b) & ~0xF000) | 0x4000); close F' "$OUT"
mv "$TMP/deps" "$OUT.d"
