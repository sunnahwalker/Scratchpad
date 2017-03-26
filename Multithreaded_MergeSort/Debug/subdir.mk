################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Main.c \
../Merge_Sorter.c \
../Thread_Pool.c 

OBJS += \
./Main.o \
./Merge_Sorter.o \
./Thread_Pool.o 

C_DEPS += \
./Main.d \
./Merge_Sorter.d \
./Thread_Pool.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


