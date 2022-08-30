################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/App/main.c 

OBJS += \
./Src/App/main.o 

C_DEPS += \
./Src/App/main.d 


# Each subdirectory must supply rules for building sources it contributes
Src/App/%.o: ../Src/App/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"E:\Egypt_FWD_Advanced track_embedded systems\Work_Space\Sprints_ARM_MC02\Src\Mcal\Inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


