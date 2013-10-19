include config/common.mk
include config/toslink-selector.mk


TARGET = toslink-selector


.DEFAULT: all
.SECONDARY: $(call objects, $(FILES)) $(call elfs, $(TARGET))


.PHONY: all
all: $(call hexs, $(TARGET)) size

.PHONY: size
size: $(call elfs, $(TARGET))
	$(SIZE) $<

.PHONY: clean
clean:
	$(call rm_gen)

.PHONY: rebuild
rebuild: clean all

.PHONY: program
program: all
	$(LPC21ISP) -control $(call hexs, $(TARGET)) /dev/ttyUSB0 115200 12000

.PHONY: count
count:
	$(call count, inc src spec)

.PHONY: test
test: 
	@$(MAKE) -C test --no-print-directory ENV=host exec

.PHONY: spec
spec: 
	@$(MAKE) -C spec --no-print-directory ENV=host exec

.PHONY: vendor
vendor: 
	@$(MAKE) -C vendor --no-print-directory


%.hex: %.elf
	$(OBJCOPY) -O ihex $< $@

%.elf: $(call objects, $(FILES))
	$(CC) $(LDFLAGS) $(call linkflags, $@) -o $@ $^ $(LIBS)

$(GEN_DIR)/%.o: $(ROOT_DIR)/%.c
	$(call mkdir_gen, $@)
	$(CC) -c $(CFLAGS) $(call dflags, $@) -o $@ $<

$(GEN_DIR)/%.o: $(ROOT_DIR)/%.cpp
	$(call mkdir_gen, $@)
	$(CXX) -c $(CXXFLAGS) $(call dflags, $@) -o $@ $<


-include $(call depends, $(FILES))
