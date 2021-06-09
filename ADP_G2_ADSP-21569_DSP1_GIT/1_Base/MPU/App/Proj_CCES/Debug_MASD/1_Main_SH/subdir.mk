################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/1_Base/MPU/App/1_Main_SH/Variation_MASD.c \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/1_Base/MPU/App/1_Main_SH/masd.c 

C_DEPS += \
./1_Main_SH/Variation_MASD.d \
./1_Main_SH/masd.d 

SRC_OBJS += \
./1_Main_SH/Variation_MASD.doj \
./1_Main_SH/masd.doj 


# Each subdirectory must supply rules for building sources it contributes
1_Main_SH/Variation_MASD.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/1_Base/MPU/App/1_Main_SH/Variation_MASD.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-4349577d55e1c7e623c54b957e77e8f4.txt -structs-do-not-overlap -no-const-strings -no-multiline -rtcheck-stack -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "1_Main_SH/Variation_MASD.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

1_Main_SH/masd.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/1_Base/MPU/App/1_Main_SH/masd.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-4349577d55e1c7e623c54b957e77e8f4.txt -structs-do-not-overlap -no-const-strings -no-multiline -rtcheck-stack -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "1_Main_SH/masd.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


