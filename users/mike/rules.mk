# Mike's userspace rules

# Add animation directory to compiler include path
# This allows keymaps to use: #include "bongo.c" instead of relative paths
ANIMATION_PATH = $(USER_PATH)/animation
VPATH += $(ANIMATION_PATH)

# Add to include path for header files
CFLAGS += -I$(ANIMATION_PATH)
CXXFLAGS += -I$(ANIMATION_PATH)
