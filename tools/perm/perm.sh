#!/usr/bin/env bash
# tools/perm/perm.sh FUNC DRAFT MINUTES JOBS: decomp-permuter search on a module draft, then every output re-scored
# by exact differing-instruction count (tools/perm/check.py), best first; 0 = match. See docs/MATCHING-TIPS.md,
# "The permuter on module drafts". Needs dk and a GNU cpp on PATH (or one at work/cppbin/cpp).
set -uo pipefail
F=$1 SRC=$(realpath "$2") MIN=$3 J=$4
cd "$(dirname "$0")/../.."
export DK_TOOLCHAIN=${DK_TOOLCHAIN:-$HOME/decomp/toolchain}
. "$DK_TOOLCHAIN/env.sh" >/dev/null 2>&1
[ -x work/cppbin/cpp ] && export PATH=$PWD/work/cppbin:$PATH
command -v cpp >/dev/null || { echo "no cpp on PATH"; exit 1; }
# Each compile leaves a dependency file next to its temp object: keep those off /tmp (often a small tmpfs).
export TMPDIR=/var/tmp/perm.$F; rm -rf "$TMPDIR"; mkdir -p "$TMPDIR"
D=nonmatchings/$F
dk perm "$F" "$SRC" --minutes 1 --jobs 1 >/dev/null 2>&1   # sets up $D: base.c, target.o, compile.sh
rm -rf "$D"/output-* "$D"/base.full.c
python3 tools/perm/strip.py "$D" "$F"
# score FUNC alone: base.c also holds the callee bodies strip.py keeps, and the permuter disassembles the whole object
sed -i "s|^objdump_command = \"\(.*\)\"|objdump_command = \"\\1 --disassemble=$F\"|" "$D/settings.toml"
echo "base: $(python3 tools/perm/check.py "$D" "$F")"
timeout --signal=INT $((MIN * 60)) python3 tools/perm/run.py "$D" -j "$J" --quiet >/dev/null 2>&1
find /tmp -maxdepth 1 -name 'permuter*' -delete
for o in "$D"/output-*; do [ -d "$o" ] && echo "$(python3 tools/perm/check.py "$D" "$F" "$o/source.c") $o"; done |
    sort -k3 -n | head -8
rm -rf "$TMPDIR"
