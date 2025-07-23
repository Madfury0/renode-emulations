# PROJECT CONFIG
TARGET := firmware
BUILD_DIR := build
SRC_DIR := src
INC_DIR := include

# ARM BUILD TOOLS
CC := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy
SIZE := arm-none-eabi-size

# COMPILER AND LINKER FLAGS
CPU := cortex-m4
FPU := -mfpu=fpv4-sp-d16
FLOAT_ABI := -mfloat-abi=hard
CSTD := -std=c11

LDLIBS := -lgcc -lc -lm
LDSTDLIB := -nostdlib

CFLAGS := -mcpu=$(CPU) -mthumb $(FPU) $(FLOAT_ABI) $(CSTD) -O0 \
		  -Wall -ffunction-sections -fdata-sections -g -I$(INC_DIR)

LDFLAGS := -T linker.ld -Wl,--gc-sections -nostartfiles \
		   -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

# SOURCE FILES AND BUILD RULES
SRC   := $(wildcard $(SRC_DIR)/*.c)
OBJ   := $(addprefix $(BUILD_DIR)/, $(notdir $(SRC:.c=.o)))
DEP   := $(OBJ:.o=.d)

all: $(BUILD_DIR)/$(TARGET).bin

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# OBJECT FILE COMPILATION
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# LINKING
$(BUILD_DIR)/$(TARGET).elf: $(OBJ)
	$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@
	$(SIZE) $@

# BIN GENERATION
$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# CLEANING
clean:
	rm -rf $(BUILD_DIR)

-include $(DEP)
.PHONY: all clean
