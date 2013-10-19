include ../config/common.mk
include ../config/toslink-selector.mk


GOOGLEMOCK_DIR = $(ROOT_DIR)/vendor/googlemock
INCLUDE_DIRS += -I$(GOOGLEMOCK_DIR)/include
INCLUDE_DIRS += -I$(GOOGLEMOCK_DIR)/gtest/include 
INCLUDE_DIRS += -I$(ROOT_DIR)/vendor/bandit
INCLUDE_DIRS += -I$(ROOT_DIR)/vendor/bandit_with_gmock
INCLUDE_DIRS += -I$(ROOT_DIR)/spec

LIB_DIRS += -L$(GOOGLEMOCK_DIR)
LIB_DIRS += -L$(GOOGLEMOCK_DIR)/gtest 

TARGET = spec
WITHOUT_FILES += main
FILES += $(call find, $(ROOT_DIR)/spec, cpp)
LIBS += -lc -lgcc -lstdc++ -lgmock -lgtest -lpthread


.DEFAULT: all
.SECONDARY: $(call objects, $(FILES)) $(call elfs, $(TARGET))


.PHONY: all
all: $(call elfs, $(TARGET))

.PHONY: exec
exec: all
	@$(call elfs, $(TARGET)) $(args)

.PHONY: clean
clean:
	$(call rm_gen)

.PHONY: rebuild
rebuild: clean all


%.elf: $(call objects, $(FILES))
	$(CXX) $(LDFLAGS) $(call linkflags, $@) -o $@ $^ $(LIBS)
	@echo "----------------------------------------------------------------------------"

$(GEN_DIR)/spec/%.o: $(ROOT_DIR)/spec/%.cpp
	$(call mkdir_gen, $@)
	$(CXX) -c $(subst -fno-exceptions,, $(CXXFLAGS)) $(call dflags, $@) -o $@ $<

$(GEN_DIR)/%.o: $(ROOT_DIR)/%.cpp
	$(call mkdir_gen, $@)
	$(CXX) -c $(CXXFLAGS) $(call dflags, $@) -o $@ $<


-include $(call depends, $(FILES))
