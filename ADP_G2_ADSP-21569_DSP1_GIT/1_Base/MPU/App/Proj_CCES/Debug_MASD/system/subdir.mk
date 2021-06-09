################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/adi_initialize.c 

C_DEPS += \
./system/adi_initialize.d 

SRC_OBJS += \
./system/adi_initialize.doj 


# Each subdirectory must supply rules for building sources it contributes
system/adi_initialize.doj: ../system/adi_initialize.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="ADP_G2-21569_Sounder_DSP1" -proc ADSP-21569 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG @includes-4349577d55e1c7e623c54b957e77e8f4.txt -structs-do-not-overlap -no-const-strings -no-multiline -rtcheck-stack -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "system/adi_initialize.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


