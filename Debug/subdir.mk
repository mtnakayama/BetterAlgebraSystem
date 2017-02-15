################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../addition.c \
../calculate.c \
../main.c \
../number_representation.c \
../parser.c \
../print.c 

OBJS += \
./addition.o \
./calculate.o \
./main.o \
./number_representation.o \
./parser.o \
./print.o 

C_DEPS += \
./addition.d \
./calculate.d \
./main.d \
./number_representation.d \
./parser.d \
./print.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -DDEBUG -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


