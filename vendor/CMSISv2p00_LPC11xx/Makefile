include ../../config/common.mk

GEN_DIR = gen
INCLUDE_DIRS = -Iinc
TARGET = liblpc11xx
FILES = $(call find, ., c)


.DEFAULT: all
.PHONY: all
all: $(call ars, $(TARGET))

.PHONY: clean
clean:
	$(call rm_gen)

.PHONY: rebuild
rebuild: clean all


$(call ars, $(TARGET)): $(call objects, $(FILES))
	$(call mkdir_gen, $@)
	$(AR) -r $@ $^

$(GEN_DIR)/%.o: %.c
	$(call mkdir_gen, $@)
	$(CC) -c $(CFLAGS) $(call dflags, $@) -o $@ $<


-include $(call depends, $(FILES))
