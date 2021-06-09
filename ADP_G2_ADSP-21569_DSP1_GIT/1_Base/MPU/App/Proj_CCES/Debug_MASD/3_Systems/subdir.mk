################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/3_Systems/SYSTEM_CACHE.c \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/3_Systems/SYSTEM_PWR.c \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/3_Systems/SYSTEM_SPU.c 

C_DEPS += \
./3_Systems/SYSTEM_CACHE.d \
./3_Systems/SYSTEM_PWR.d \
./3_Systems/SYSTEM_SPU.d 

SRC_OBJS += \
./3_Systems/SYSTEM_CACHE.doj \
./3_Systems/SYSTEM_PWR.doj \
./3_Systems/SYSTEM_SPU.doj 


# Each subdirectory must supply rules for building sources it contributes
3_Systems/SYSTEM_CACHE.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/3_Systems/SYSTEM_CACHE.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-4349577d55e1c7e623c54b957e77e8f4.txt -structs-do-not-overlap -no-const-strings -no-multiline -rtcheck-stack -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "3_Systems/SYSTEM_CACHE.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

3_Systems/SYSTEM_PWR.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/3_Systems/SYSTEM_PWR.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-4349577d55e1c7e623c54b957e77e8f4.txt -structs-do-not-overlap -no-const-strings -no-multiline -rtcheck-stack -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "3_Systems/SYSTEM_PWR.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

3_Systems/SYSTEM_SPU.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/3_Systems/SYSTEM_SPU.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-4349577d55e1c7e623c54b957e77e8f4.txt -structs-do-not-overlap -no-const-strings -no-multiline -rtcheck-stack -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "3_Systems/SYSTEM_SPU.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


