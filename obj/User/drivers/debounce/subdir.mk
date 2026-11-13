################################################################################
# MRS Version: 2.5.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/drivers/debounce/debounce.c 

C_DEPS += \
./User/drivers/debounce/debounce.d 

OBJS += \
./User/drivers/debounce/debounce.o 

DIR_OBJS += \
./User/drivers/debounce/*.o \

DIR_DEPS += \
./User/drivers/debounce/*.d \

DIR_EXPANDS += \
./User/drivers/debounce/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
User/drivers/debounce/%.o: ../User/drivers/debounce/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -ffreestanding -Wunused -Wuninitialized -g -I"/home/harry/mounriver-studio-projects/CH32MK/Debug" -I"/home/harry/mounriver-studio-projects/CH32MK/Core" -I"/home/harry/mounriver-studio-projects/CH32MK/User" -I"/home/harry/mounriver-studio-projects/CH32MK/Peripheral/inc" -I"/home/harry/mounriver-studio-projects/CH32MK/tinyusb" -I"/home/harry/mounriver-studio-projects/CH32MK/tinyusb/src" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/usb" -I"/home/harry/mounriver-studio-projects/CH32MK/User/config" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/gpio" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/matrix" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/debounce" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/keycodes" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/split" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/systick" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/layers" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/process_keymap" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/events" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/process_matrix" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/engine" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

