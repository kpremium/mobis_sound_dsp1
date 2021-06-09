################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := ${ComSpec}

-include ../makefile.init

RM := clean

# All of the sources participating in the build are defined here
-include sources.mk
-include system/startup_ldf/subdir.mk
-include system/pinmux/GeneratedSources/subdir.mk
-include system/subdir.mk
-include ldf/subdir.mk
-include 4_Drivers/subdir.mk
-include 3_Systems/subdir.mk
-include 2_Middle/subdir.mk
-include 1_Main_SH/subdir.mk
-include 0_Common/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(DSP_DEPS)),)
-include $(DSP_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
DXE += \
ADP_G2-21569_Sounder_DSP1.dxe \

LINKER_LOG_OUTPUTS += \
linker_log.xml \

DEVICE_PROGRAMMER_OUTPUTS += \
program_device \

OBJS := $(SRC_OBJS)
# Quote makefile variable : OBJS 
OBJS := $(subst \ ,@, $(OBJS))
OBJS := $(foreach var, $(OBJS), "$(subst @, ,$(var))")
# Quote makefile variable : C_UPPER_DEPS 
C_UPPER_DEPS := $(subst \ ,@, $(C_UPPER_DEPS))
C_UPPER_DEPS := $(foreach var, $(C_UPPER_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : S_DEPS 
S_DEPS := $(subst \ ,@, $(S_DEPS))
S_DEPS := $(foreach var, $(S_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : C_DEPS 
C_DEPS := $(subst \ ,@, $(C_DEPS))
C_DEPS := $(foreach var, $(C_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : DSP_DEPS 
DSP_DEPS := $(subst \ ,@, $(DSP_DEPS))
DSP_DEPS := $(foreach var, $(DSP_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : CC_DEPS 
CC_DEPS := $(subst \ ,@, $(CC_DEPS))
CC_DEPS := $(foreach var, $(CC_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : C++_DEPS 
C++_DEPS := $(subst \ ,@, $(C++_DEPS))
C++_DEPS := $(foreach var, $(C++_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : CXX_DEPS 
CXX_DEPS := $(subst \ ,@, $(CXX_DEPS))
CXX_DEPS := $(foreach var, $(CXX_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : ASM_DEPS 
ASM_DEPS := $(subst \ ,@, $(ASM_DEPS))
ASM_DEPS := $(foreach var, $(ASM_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : CPP_DEPS 
CPP_DEPS := $(subst \ ,@, $(CPP_DEPS))
CPP_DEPS := $(foreach var, $(CPP_DEPS), "$(subst @, ,$(var))")
LDR += \
ADP_G2-21569_Sounder_DSP1.ldr \


# All Target
all: ADP_G2-21569_Sounder_DSP1.ldr

# Tool invocations
ADP_G2-21569_Sounder_DSP1.ldr: $(DXE) $(SRC_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: CrossCore SHARC Loader'
	elfloader -v -proc ADSP-21569 -si-revision any -bspimaster -fhex -width 8 -bcode 10 -init "D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/1_Base/MPU/App/Proj_CCES/../../Init/2156x_init/Release/2156x_init.dxe" -o "ADP_G2-21569_Sounder_DSP1.ldr" "ADP_G2-21569_Sounder_DSP1.dxe"
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

ADP_G2-21569_Sounder_DSP1.dxe: $(LDF_SRCS) $(SRC_OBJS)
	@echo 'Invoking: CrossCore SHARC Linker'
	cc21k -proc ADSP-21569 -si-revision any -rtcheck-stack -TD:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/1_Base/MPU/App/Proj_CCES/system/startup_ldf/app.ldf -no-mem -map ADP_G2-21569_Sounder_DSP1.map.xml -LD:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/1_Base/MPU/App/Proj_CCES/Debug_MASD/system/startup_ldf -L/Target/Lib-CCES -LC:/Analog\ Devices/SoftwareModules/SigmaStudioForSHARC-SH-Rel4.6.0/Target/Lib-CCES -flags-link -MDCORE0,-MDDEBUG -flags-link -i,D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/1_Base/MPU/App/Proj_CCES/ldf -flags-link -e -flags-link -ev -add-debug-libpaths -flags-link libadi_sigma_sharc_comm_2156x_Core1.dlb, -flags-link libadi_sigma_sharc_215xx.dlb -o ADP_G2-21569_Sounder_DSP1.dxe @input-file.txt  -flags-link -od,.\.
	@echo 'Finished building: $@'
	@echo ' '

linker_log.xml: ADP_G2-21569_Sounder_DSP1.dxe $(LDF_SRCS) $(SRC_OBJS)

program_device: $(LDR) $(SRC_OBJS)
	@echo 'Invoking: CrossCore SHARC Device Programmer'
	cldp -proc ADSP-21569 -verbose -cmd prog -driver "D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/1_Base/MPU/App/Proj_CCES/../../../Utility/JtagFlash/MT25QL512ABB_dpia_2156x.dxe" -erase affected -emu ice-2000 -format hex  -file $(LDR)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(LINKER_LOG_OUTPUTS)$(DEVICE_PROGRAMMER_OUTPUTS)$(C_UPPER_DEPS)$(S_DEPS)$(C_DEPS)$(DXE)$(DSP_DEPS)$(CC_DEPS)$(C++_DEPS)$(OBJS)$(CXX_DEPS)$(ASM_DEPS)$(LDR)$(CPP_DEPS) ADP_G2-21569_Sounder_DSP1.ldr
	-@echo ' '

post-build:
	-cmd /C ..\PostScripts.bat ADP_G2-21569_Sounder_DSP1 Debug_MASD
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
