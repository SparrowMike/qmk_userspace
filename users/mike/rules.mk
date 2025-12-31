# Mike's userspace rules

# Add userspace source files
SRC += mike.c

# Add animation directory to compiler include path
# This allows keymaps to use: #include "bongo.c" instead of relative paths
ANIMATION_PATH = $(USER_PATH)/animation
VPATH += $(ANIMATION_PATH)

# Add to include path for header files
CFLAGS += -I$(ANIMATION_PATH)
CXXFLAGS += -I$(ANIMATION_PATH)

# Common features across all keyboards
# NOTE: CONVERT_TO must be in keyboard-specific rules.mk
COMBO_ENABLE = yes
WPM_ENABLE = yes
OLED_ENABLE = yes
OLED_DRIVER = ssd1306
CAPS_WORD_ENABLE = yes

VIA_ENABLE = yes
