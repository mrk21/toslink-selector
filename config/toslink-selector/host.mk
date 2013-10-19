INCLUDE_DIRS += -I$(ROOT_DIR)/spec/test_double/inc
WITHOUT_FILES  = handlers
-WITHOUT_FILES += $(notdir $(call find, $(ROOT_DIR)/src/device, cpp))
FILES = $(call find, $(ROOT_DIR)/src, cpp, $(addprefix -not -name , $(addsuffix .*, $(WITHOUT_FILES))))
