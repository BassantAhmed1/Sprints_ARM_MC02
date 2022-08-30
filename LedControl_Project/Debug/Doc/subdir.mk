################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Doc/SourceFileTemplate.c 

OBJS += \
./Doc/SourceFileTemplate.o 

C_DEPS += \
./Doc/SourceFileTemplate.d 


# Each subdirectory must supply rules for building sources it contributes
Doc/%.o: ../Doc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"E:\Egypt_FWD_Advanced track_embedded systems\Work_Space\Sprints_ARM_MC02\Src\Mcal\Inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


