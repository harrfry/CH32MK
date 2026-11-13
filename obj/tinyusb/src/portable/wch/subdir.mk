################################################################################
# MRS Version: 2.5.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tinyusb/src/portable/wch/dcd_ch32_usbfs.c \
../tinyusb/src/portable/wch/dcd_ch32_usbhs.c \
../tinyusb/src/portable/wch/hcd_ch32_usbfs.c 

C_DEPS += \
./tinyusb/src/portable/wch/dcd_ch32_usbfs.d \
./tinyusb/src/portable/wch/dcd_ch32_usbhs.d \
./tinyusb/src/portable/wch/hcd_ch32_usbfs.d 

OBJS += \
./tinyusb/src/portable/wch/dcd_ch32_usbfs.o \
./tinyusb/src/portable/wch/dcd_ch32_usbhs.o \
./tinyusb/src/portable/wch/hcd_ch32_usbfs.o 

DIR_OBJS += \
./tinyusb/src/portable/wch/*.o \

DIR_DEPS += \
./tinyusb/src/portable/wch/*.d \

DIR_EXPANDS += \
./tinyusb/src/portable/wch/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
tinyusb/src/portable/wch/%.o: ../tinyusb/src/portable/wch/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -ffreestanding -Wunused -Wuninitialized -g -I"/home/harry/mounriver-studio-projects/CH32MK/Debug" -I"/home/harry/mounriver-studio-projects/CH32MK/Core" -I"/home/harry/mounriver-studio-projects/CH32MK/User" -I"/home/harry/mounriver-studio-projects/CH32MK/Peripheral/inc" -I"/home/harry/mounriver-studio-projects/CH32MK/tinyusb" -I"/home/harry/mounriver-studio-projects/CH32MK/tinyusb/src" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/usb" -I"/home/harry/mounriver-studio-projects/CH32MK/User/config" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/gpio" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/matrix" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/debounce" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/keycodes" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/split" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/systick" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/layers" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/process_keymap" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/events" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/process_matrix" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

