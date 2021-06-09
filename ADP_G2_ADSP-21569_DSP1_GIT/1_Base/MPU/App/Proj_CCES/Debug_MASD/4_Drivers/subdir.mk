################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_ASRC.c \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_DAI.c \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_DMA.c \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_FLASH.c \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_GPIO.c \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_Interrupt.c \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_LinkPort.c \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_PCG.c \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_SPDIF.c \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_SPI.c \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_SPORT.c \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_Timer.c \
D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_UART.c 

C_DEPS += \
./4_Drivers/DRV_ASRC.d \
./4_Drivers/DRV_DAI.d \
./4_Drivers/DRV_DMA.d \
./4_Drivers/DRV_FLASH.d \
./4_Drivers/DRV_GPIO.d \
./4_Drivers/DRV_Interrupt.d \
./4_Drivers/DRV_LinkPort.d \
./4_Drivers/DRV_PCG.d \
./4_Drivers/DRV_SPDIF.d \
./4_Drivers/DRV_SPI.d \
./4_Drivers/DRV_SPORT.d \
./4_Drivers/DRV_Timer.d \
./4_Drivers/DRV_UART.d 

SRC_OBJS += \
./4_Drivers/DRV_ASRC.doj \
./4_Drivers/DRV_DAI.doj \
./4_Drivers/DRV_DMA.doj \
./4_Drivers/DRV_FLASH.doj \
./4_Drivers/DRV_GPIO.doj \
./4_Drivers/DRV_Interrupt.doj \
./4_Drivers/DRV_LinkPort.doj \
./4_Drivers/DRV_PCG.doj \
./4_Drivers/DRV_SPDIF.doj \
./4_Drivers/DRV_SPI.doj \
./4_Drivers/DRV_SPORT.doj \
./4_Drivers/DRV_Timer.doj \
./4_Drivers/DRV_UART.doj 


# Each subdirectory must supply rules for building sources it contributes
4_Drivers/DRV_ASRC.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_ASRC.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-4349577d55e1c7e623c54b957e77e8f4.txt -structs-do-not-overlap -no-const-strings -no-multiline -rtcheck-stack -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "4_Drivers/DRV_ASRC.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

4_Drivers/DRV_DAI.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_DAI.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-4349577d55e1c7e623c54b957e77e8f4.txt -structs-do-not-overlap -no-const-strings -no-multiline -rtcheck-stack -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "4_Drivers/DRV_DAI.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

4_Drivers/DRV_DMA.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_DMA.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-4349577d55e1c7e623c54b957e77e8f4.txt -structs-do-not-overlap -no-const-strings -no-multiline -rtcheck-stack -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "4_Drivers/DRV_DMA.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

4_Drivers/DRV_FLASH.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_FLASH.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-4349577d55e1c7e623c54b957e77e8f4.txt -structs-do-not-overlap -no-const-strings -no-multiline -rtcheck-stack -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "4_Drivers/DRV_FLASH.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

4_Drivers/DRV_GPIO.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_GPIO.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-4349577d55e1c7e623c54b957e77e8f4.txt -structs-do-not-overlap -no-const-strings -no-multiline -rtcheck-stack -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "4_Drivers/DRV_GPIO.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

4_Drivers/DRV_Interrupt.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_Interrupt.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-4349577d55e1c7e623c54b957e77e8f4.txt -structs-do-not-overlap -no-const-strings -no-multiline -rtcheck-stack -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "4_Drivers/DRV_Interrupt.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

4_Drivers/DRV_LinkPort.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_LinkPort.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-4349577d55e1c7e623c54b957e77e8f4.txt -structs-do-not-overlap -no-const-strings -no-multiline -rtcheck-stack -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "4_Drivers/DRV_LinkPort.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

4_Drivers/DRV_PCG.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_PCG.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-4349577d55e1c7e623c54b957e77e8f4.txt -structs-do-not-overlap -no-const-strings -no-multiline -rtcheck-stack -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "4_Drivers/DRV_PCG.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

4_Drivers/DRV_SPDIF.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_SPDIF.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-4349577d55e1c7e623c54b957e77e8f4.txt -structs-do-not-overlap -no-const-strings -no-multiline -rtcheck-stack -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "4_Drivers/DRV_SPDIF.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

4_Drivers/DRV_SPI.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_SPI.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-4349577d55e1c7e623c54b957e77e8f4.txt -structs-do-not-overlap -no-const-strings -no-multiline -rtcheck-stack -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "4_Drivers/DRV_SPI.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

4_Drivers/DRV_SPORT.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_SPORT.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-4349577d55e1c7e623c54b957e77e8f4.txt -structs-do-not-overlap -no-const-strings -no-multiline -rtcheck-stack -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "4_Drivers/DRV_SPORT.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

4_Drivers/DRV_Timer.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_Timer.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-4349577d55e1c7e623c54b957e77e8f4.txt -structs-do-not-overlap -no-const-strings -no-multiline -rtcheck-stack -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "4_Drivers/DRV_Timer.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

4_Drivers/DRV_UART.doj: D:/work/HM_Sound/work_space/AnyRactive_work/DSP1/ADP_G2_ADSP-21569_DSP1_GIT/0_Framework/Framework/4_Drivers/DRV_UART.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-4349577d55e1c7e623c54b957e77e8f4.txt -structs-do-not-overlap -no-const-strings -no-multiline -rtcheck-stack -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "4_Drivers/DRV_UART.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


