TOOLCHAIN = arm-none-eabi-
CFLAGS  += -mcpu=cortex-m0 -mthumb
LDFLAGS += -mcpu=cortex-m0 -mthumb
LDFLAGS += -T$(LD_SCRIPT)
LD_SCRIPT = $(ROOT_DIR)/config/lpc1114fn28.ld
