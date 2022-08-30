################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Mcal/IntCtrl.c \
../Src/Mcal/TM4C123GH6PM_GPIO.c \
../Src/Mcal/TM4C123GH6PM_GPT.c \
../Src/Mcal/TM4c123GH6PM_SysTick.c 

OBJS += \
./Src/Mcal/IntCtrl.o \
./Src/Mcal/TM4C123GH6PM_GPIO.o \
./Src/Mcal/TM4C123GH6PM_GPT.o \
./Src/Mcal/TM4c123GH6PM_SysTick.o 

C_DEPS += \
./Src/Mcal/IntCtrl.d \
./Src/Mcal/TM4C123GH6PM_GPIO.d \
./Src/Mcal/TM4C123GH6PM_GPT.d \
./Src/Mcal/TM4c123GH6PM_SysTick.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Mcal/%.o: ../Src/Mcal/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"E:\Egypt_FWD_Advanced track_embedded systems\Work_Space\Sprints_ARM_MC02\Src\Mcal\Inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


