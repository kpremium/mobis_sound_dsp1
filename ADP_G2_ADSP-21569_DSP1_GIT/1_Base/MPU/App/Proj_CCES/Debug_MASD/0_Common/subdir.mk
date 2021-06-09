################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/0_Common/adi_ss_fw_utility.asm \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/0_Common/adi_ss_gmap.asm 

LDF_SRCS += \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/0_Common/adi_ss_app.ldf 

C_SRCS += \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/0_Common/App_MainTask.c \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/0_Common/utility.c 

C_DEPS += \
./0_Common/App_MainTask.d \
./0_Common/utility.d 

SRC_OBJS += \
./0_Common/App_MainTask.doj \
./0_Common/adi_ss_fw_utility.doj \
./0_Common/adi_ss_gmap.doj \
./0_Common/utility.doj 

ASM_DEPS += \
./0_Common/adi_ss_fw_utility.d \
./0_Common/adi_ss_gmap.d 


# Each subdirectory must supply rules for building sources it contributes
0_Common/App_MainTask.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/0_Common/App_MainTask.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-4349577d55e1c7e623c54b957e77e8f4.txt -structs-do-not-overlap -no-const-strings -no-multiline -rtcheck-stack -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "0_Common/App_MainTask.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Common/adi_ss_fw_utility.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/0_Common/adi_ss_fw_utility.asm
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC Assembler'
	easm21k -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -si-revision any -g -DCORE0 -D_DEBUG @includes-364cb69aa036130b8eccb86ac2b920f2.txt -swc -char-size-8 -gnu-style-dependencies -MM -Mo "0_Common/adi_ss_fw_utility.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Common/adi_ss_gmap.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/0_Common/adi_ss_gmap.asm
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC Assembler'
	easm21k -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -si-revision any -g -DCORE0 -D_DEBUG @includes-364cb69aa036130b8eccb86ac2b920f2.txt -swc -char-size-8 -gnu-style-dependencies -MM -Mo "0_Common/adi_ss_gmap.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Common/utility.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/0_Common/utility.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-4349577d55e1c7e623c54b957e77e8f4.txt -structs-do-not-overlap -no-const-strings -no-multiline -rtcheck-stack -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "0_Common/utility.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


