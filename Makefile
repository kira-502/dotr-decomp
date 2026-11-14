# Made by decomp-kit (dk new). Build settings live in dk.json; dk writes config.mk.
include config.mk

SPLAT_CFG := config/main.yaml
LD_SCRIPT := linker/main.ld
LD_SYMS   := config/linker_syms.txt
# The main program's old func_ names, aliases of its real ones (the code modules use them).
OLD_NAMES := config/old_names.txt
# The old D_ data names, aliases of the real ones (config/symbol_addrs.txt).
OLD_DATA  := config/old_data_names.txt
# batzpup's names for functions where ours differ (his Ghidra project), linker aliases too.
GHIDRA_NAMES := config/ghidra_names.txt
WARM_LIST := config/warm_files.txt
# Words the shipped game overwrote after its build (tools/postpatch.py); applied to the linked ELF.
POSTPATCH := config/postpatch.txt
BUILD     := build
ELF       := $(BUILD)/main.elf
OUT_EXE   := $(BUILD)/$(EXE)

AS      := mipsel-none-elf-as
LD      := mipsel-none-elf-ld
OBJCOPY := mipsel-none-elf-objcopy

# The code modules (src/mod, asm/*/mod) build apart from the executable: see "Code modules" below.
ASM_SRCS := $(shell find asm -name '*.s' -not -path '*/nonmatchings/*' -not -path '*/matchings/*' -not -path 'asm/data/mod/*' 2>/dev/null)
C_SRCS   := $(shell find src -name '*.c' -not -path 'src/mod/*' 2>/dev/null)
BIN_SRCS := $(shell find assets -name '*.bin' 2>/dev/null)
OBJS     := $(ASM_SRCS:%=$(BUILD)/%.o) $(C_SRCS:%=$(BUILD)/%.o) $(BIN_SRCS:%=$(BUILD)/%.o)
# Files tools/cc.sh compiles warm (see there). A file put on the list compiles again; one
# taken off does too, through the .d file its warm build wrote.
WARM_SRCS := $(shell sed 's/\#.*//' $(WARM_LIST) 2>/dev/null)
# Files tools/cc.sh compiles with an EE GCC (Sony's libraries), the same way.
GCC_LIST  := config/gcc_files.txt
GCC_SRCS  := $(shell sed 's/\#.*//' $(GCC_LIST) 2>/dev/null | awk '{ print $$1 }')

.PHONY: all build check split clean modules check-modules split-modules
all: check

split:
	@rm -rf asm $(BUILD) $(LD_SCRIPT) linker/undefined_*_auto.txt linker/mod
	@mkdir -p $(BUILD)
	@python3 -m splat split $(SPLAT_CFG) > $(BUILD)/split.log 2>&1 || { tail -20 $(BUILD)/split.log; exit 1; }
	@if [ -f tools/fix_asm.py ]; then python3 tools/fix_asm.py; fi

build:
	@[ -f $(LD_SCRIPT) ] || $(MAKE) --no-print-directory split
	@$(MAKE) --no-print-directory $(OUT_EXE)
	@[ -f $(MOD_MK) ] || $(MAKE) --no-print-directory split-modules
	@$(MAKE) --no-print-directory modules

check: build
	@echo "$(TARGET_SHA)  $(OUT_EXE)" | sha1sum -c --quiet - && echo "OK: $(OUT_EXE) matches the original"
	@python3 tools/modules.py check

# ---- Code modules: the 762 Metrowerks overlays of DATA/*MODULE.MRG (tools/modules.py). Each one is its own
# program: src/mod/<name>.c (+ the literal pool and .data in asm/data/mod/) linked at 0x1E00080 and packed back
# into an MWo3 file, compared with the disc's (config/modules.tsv). Their objects carry no header dependencies:
# a module rebuilds when its own C file changes (dk accept recompiles the module it touches).
MOD_TABLE := config/modules.tsv
MOD_MK    := linker/mod/modules.mk
MODS      := $(shell awk 'NR > 1 { print $$1 }' $(MOD_TABLE) 2>/dev/null)

split-modules: $(ELF)
	@rm -rf asm/nonmatchings/mod asm/matchings/mod asm/data/mod linker/mod $(BUILD)/modsplit $(BUILD)/modules \
		$(BUILD)/src/mod $(BUILD)/asm/data/mod
	@[ -d assets/modules ] || python3 tools/modules.py extract
	@python3 tools/modules.py split

modules: $(MODS:%=$(BUILD)/modules/%.mwo)

check-modules: modules
	@python3 tools/modules.py check

$(BUILD)/modules/%.elf: linker/mod/%.ld $(LD_SYMS)
	@mkdir -p $(dir $@)
	@$(LD) -EL -T linker/mod/$*.ld -T linker/mod/$*.funcs.txt -T linker/mod/$*.syms.txt -T $(LD_SYMS) \
		-Map $(BUILD)/modules/$*.map -o $@

$(BUILD)/modules/%.mwo: $(BUILD)/modules/%.elf $(MOD_TABLE)
	@python3 tools/modules.py pack $* $< $@

# Module C compiles warm (tools/cc.sh): their float casts call fptoui/fptosi as a warm compiler does, and every
# cold match so far also matches warm (OVERLAYS-COMPILER.md). dk try does the same for module functions.
# A few modules were built in another warm state: config/mod_warm.txt (read by tools/cc.sh) sets their level.
$(BUILD)/src/mod/%.c.o: export DK_WARM := 1

-include $(MOD_MK)

$(BUILD)/%.s.o: %.s
	@mkdir -p $(dir $@)
	@$(AS) $(AS_FLAGS) -I. -Iinclude -o $@ $<

# Through the assembler (not ld -b binary) so its ABI flags match every other object.
$(BUILD)/%.bin.o: %.bin
	@mkdir -p $(dir $@)
	@printf '.section .data\n.incbin "%s"\n' $< > $@.s
	@$(AS) $(AS_FLAGS) -o $@ $@.s

$(BUILD)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@tools/cc.sh $< $@

$(WARM_SRCS:%=$(BUILD)/%.o): $(WARM_LIST)
$(GCC_SRCS:%=$(BUILD)/%.o): $(GCC_LIST)

$(ELF): $(OBJS) $(LD_SCRIPT) $(LD_SYMS) $(OLD_NAMES) $(OLD_DATA) $(GHIDRA_NAMES) $(wildcard $(POSTPATCH))
	@$(LD) -EL -T $(LD_SCRIPT) -T linker/undefined_syms_auto.txt -T linker/undefined_funcs_auto.txt \
		-T $(LD_SYMS) -T $(OLD_NAMES) -T $(OLD_DATA) -T $(GHIDRA_NAMES) -Map $(BUILD)/main.map -o $@
	@python3 tools/postpatch.py $@ $(POSTPATCH) || { rm -f $@; exit 1; }

$(OUT_EXE): $(ELF)
	@$(OBJCOPY) -O binary $< $@

clean:
	rm -rf $(BUILD)

-include $(C_SRCS:%=$(BUILD)/%.o.d)
