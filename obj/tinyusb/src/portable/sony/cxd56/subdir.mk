################################################################################
# MRS Version: 2.5.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tinyusb/src/portable/sony/cxd56/dcd_cxd56.c 

C_DEPS += \
./tinyusb/src/portable/sony/cxd56/dcd_cxd56.d 

OBJS += \
./tinyusb/src/portable/sony/cxd56/dcd_cxd56.o 

DIR_OBJS += \
./tinyusb/src/portable/sony/cxd56/*.o \

DIR_DEPS += \
./tinyusb/src/portable/sony/cxd56/*.d \

DIR_EXPANDS += \
./tinyusb/src/portable/sony/cxd56/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
tinyusb/src/portable/sony/cxd56/%.o: ../tinyusb/src/portable/sony/cxd56/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -ffreestanding -Wunused -Wuninitialized -g -I"/home/harry/mounriver-studio-projects/CH32MK/Debug" -I"/home/harry/mounriver-studio-projects/CH32MK/Core" -I"/home/harry/mounriver-studio-projects/CH32MK/User" -I"/home/harry/mounriver-studio-projects/CH32MK/Peripheral/inc" -I"/home/harry/mounriver-studio-projects/CH32MK/tinyusb" -I"/home/harry/mounriver-studio-projects/CH32MK/tinyusb/src" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/usb" -I"/home/harry/mounriver-studio-projects/CH32MK/User/config" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/gpio" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/matrix" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/debounce" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/keycodes" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/split" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/systick" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/layers" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/process_keymap" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/events" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/process_matrix" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

