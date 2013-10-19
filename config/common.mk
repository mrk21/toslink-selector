MAKEFILE := $(word $(words $(MAKEFILE_LIST)), $(MAKEFILE_LIST))
MAKEFILE_DIR := $(dir $(MAKEFILE))
ROOT_DIR := $(shell cd $(MAKEFILE_DIR)..; pwd -P)
ENV ?= target
include $(MAKEFILE_DIR)/common/$(ENV).mk

CC      = $(TOOLCHAIN)gcc
CXX     = $(TOOLCHAIN)g++
LD      = $(TOOLCHAIN)ld
AS      = $(TOOLCHAIN)as
OBJCOPY = $(TOOLCHAIN)objcopy
OBJDUMP = $(TOOLCHAIN)objdump
AR      = $(TOOLCHAIN)ar
SIZE    = $(TOOLCHAIN)size
NM      = $(TOOLCHAIN)nm
LPC21ISP = lpc21isp


CFLAGS += -fmessage-length=0
CFLAGS += -fno-builtin
CFLAGS += -ffunction-sections
CFLAGS += -fdata-sections
CFLAGS += -Os -g3 -Wall
CFLAGS += $(DEFINE)
CFLAGS += $(INCLUDE_DIRS)

CXXFLAGS += -std=c++11
CXXFLAGS += -fno-rtti
CXXFLAGS += -fno-exceptions
CXXFLAGS += -fno-threadsafe-statics
CXXFLAGS += $(CFLAGS)

# $(call dflags, $filepath)
define dflags
 -MMD -MP -MF"$(basename $1).d" -MT"$(basename $1).o"
endef


LDFLAGS += $(LIB_DIRS)

# $(call mapflags, $filepath)
define linkflags
 -Xlinker --gc-sections -Xlinker -Map="$(basename $1).map"
endef


# $(call find, $target, $ext[, $expr])
define find
 $(shell find $1 -name '*.$(strip $2)' -not -name '.*' $3 | sed -e 's/.$(strip $2)$$//')
endef

# $(call count, $target)
define count
 find $1 -name "*.c" -not -name ".*" -or -name "*.cpp" -not -name ".*" -or -name "*.h" -not -name ".*" -or -name "*.hpp" -not -name ".*" | xargs wc -l
endef


GEN_DIR = $(ROOT_DIR)/gen/$(ENV)

# $(call objects, $files)
define objects
 $(call gen_path, $(addsuffix .o, $1))
endef

# $(call depends, $files)
define depends
 $(call gen_path, $(addsuffix .d, $1))
endef

# $(call hexs, $files)
define hexs
 $(call gen_path, $(addsuffix .hex, $1))
endef

# $(call ars, $files)
define ars
 $(call gen_path, $(addsuffix .a, $1))
endef

# $(call elfs, $files)
define elfs
 $(call gen_path, $(addsuffix .elf, $1))
endef


# $(call gen_path, $files)
define gen_path
 $(addprefix $(GEN_DIR)/, $(subst $(ROOT_DIR)/,, $1))
endef

# $(call rm_gen)
define rm_gen
 $(RM) -r $(GEN_DIR)
endef

# $(call mkdir_gen, $path)
define mkdir_gen
 @mkdir -p $(dir $1)
endef
