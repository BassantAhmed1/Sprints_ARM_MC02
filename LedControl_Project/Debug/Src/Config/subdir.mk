################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Config/GPIO_Lcfg.c \
../Src/Config/GPT_Cfg.c \
../Src/Config/IntCtrl_Lcfg.c 

OBJS += \
./Src/Config/GPIO_Lcfg.o \
./Src/Config/GPT_Cfg.o \
./Src/Config/IntCtrl_Lcfg.o 

C_DEPS += \
./Src/Config/GPIO_Lcfg.d \
./Src/Config/GPT_Cfg.d \
./Src/Config/IntCtrl_Lcfg.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Config/%.o: ../Src/Config/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"E:\Egypt_FWD_Advanced track_embedded systems\Work_Space\Sprints_ARM_MC02\Src\Mcal\Inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


