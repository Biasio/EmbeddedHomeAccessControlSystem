################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /Applications/ti/ccs1280/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./startup_msp432p401r_ccs.obj" \
"./system_msp432p401r.obj" \
"./src/HAL_I2C.obj" \
"./src/HAL_OPT3001.obj" \
"./src/display.obj" \
"./src/door_lock_system.obj" \
"./src/fsm.obj" \
"./src/joystick.obj" \
"./src/push_button.obj" \
"./src/LCD_src/Crystalfontz128x128_ST7735.obj" \
"./src/LCD_src/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.obj" \
"../msp432p401r.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-lgrlib.a \
-l"/Users/biasio/Documents/Documents_Nextcloud/UNITN/EMBEDDED/dev-biasio/workspace_1/simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/driverlib/ccs/msp432p4xx_driverlib.lib" \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include src/subdir_vars.mk
-include src/LCD_src/subdir_vars.mk
-include subdir_rules.mk
-include src/subdir_rules.mk
-include src/LCD_src/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
ShortStaysAccessControlSystem.out 

EXE_OUTPUTS__QUOTED += \
"ShortStaysAccessControlSystem.out" 


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "ShortStaysAccessControlSystem.out"

# Tool invocations
ShortStaysAccessControlSystem.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"/Applications/ti/ccs1280/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --advice:power="all" --define=MSP_EXP432P401R --define=MSP432P401R --define=DeviceFamily_MSP432P4x1x --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"ShortStaysAccessControlSystem.map" --heap_size=1024 --stack_size=512 -i"/Users/biasio/Documents/Documents_Nextcloud/UNITN/EMBEDDED/dev-biasio/workspace_1/simplelink_msp432p4_sdk_3_40_01_02/kernel/nortos/packages/ti/dpl/lib" -i"/Users/biasio/Documents/Documents_Nextcloud/UNITN/EMBEDDED/dev-biasio/workspace_1/simplelink_msp432p4_sdk_3_40_01_02/source/ti/grlib/lib/ccs/m4f" -i"/Users/biasio/Documents/Documents_Nextcloud/UNITN/EMBEDDED/dev-biasio/workspace_1/simplelink_msp432p4_sdk_3_40_01_02/source/ti/grlib/lib/ccs" -i"/Users/biasio/Documents/Documents_Nextcloud/UNITN/EMBEDDED/dev-biasio/workspace_1/simplelink_msp432p4_sdk_3_40_01_02/examples/nortos/MSP_EXP432P401R/demos/boostxl_edumkii_lightsensor_msp432p401r/LcdDriver" -i"/Users/biasio/Documents/Documents_Nextcloud/UNITN/EMBEDDED/dev-biasio/workspace_1/simplelink_msp432p4_sdk_3_40_01_02/source/ti/drivers/lib" -i"/Users/biasio/Documents/Documents_Nextcloud/UNITN/EMBEDDED/dev-biasio/workspace_1/simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/driverlib" -i"/Applications/ti/ccs1280/ccs/ccs_base/arm/include" -i"/Applications/ti/ccs1280/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/lib" -i"/Applications/ti/ccs1280/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="ShortStaysAccessControlSystem_linkInfo.xml" --rom_model -o "ShortStaysAccessControlSystem.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "startup_msp432p401r_ccs.obj" "system_msp432p401r.obj" "src/HAL_I2C.obj" "src/HAL_OPT3001.obj" "src/display.obj" "src/door_lock_system.obj" "src/fsm.obj" "src/joystick.obj" "src/push_button.obj" "src/LCD_src/Crystalfontz128x128_ST7735.obj" "src/LCD_src/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.obj" 
	-$(RM) "startup_msp432p401r_ccs.d" "system_msp432p401r.d" "src/HAL_I2C.d" "src/HAL_OPT3001.d" "src/display.d" "src/door_lock_system.d" "src/fsm.d" "src/joystick.d" "src/push_button.d" "src/LCD_src/Crystalfontz128x128_ST7735.d" "src/LCD_src/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

