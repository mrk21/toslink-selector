CMSIS_DIR = $(ROOT_DIR)/vendor/CMSISv2p00_LPC11xx
INCLUDE_DIRS += -I$(CMSIS_DIR)/inc
LIB_DIRS += -L$(CMSIS_DIR)/gen
LIBS += -llpc11xx

FILES = $(call find, $(ROOT_DIR)/src, c) $(call find, $(ROOT_DIR)/src, cpp)
