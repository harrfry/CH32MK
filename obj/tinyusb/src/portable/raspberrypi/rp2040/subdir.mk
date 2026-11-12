################################################################################
# MRS Version: 2.5.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tinyusb/src/portable/raspberrypi/rp2040/dcd_rp2040.c \
../tinyusb/src/portable/raspberrypi/rp2040/hcd_rp2040.c \
../tinyusb/src/portable/raspberrypi/rp2040/rp2040_usb.c 

C_DEPS += \
./tinyusb/src/portable/raspberrypi/rp2040/dcd_rp2040.d \
./tinyusb/src/portable/raspberrypi/rp2040/hcd_rp2040.d \
./tinyusb/src/portable/raspberrypi/rp2040/rp2040_usb.d 

OBJS += \
./tinyusb/src/portable/raspberrypi/rp2040/dcd_rp2040.o \
./tinyusb/src/portable/raspberrypi/rp2040/hcd_rp2040.o \
./tinyusb/src/portable/raspberrypi/rp2040/rp2040_usb.o 

DIR_OBJS += \
./tinyusb/src/portable/raspberrypi/rp2040/*.o \

DIR_DEPS += \
./tinyusb/src/portable/raspberrypi/rp2040/*.d \

DIR_EXPANDS += \
./tinyusb/src/portable/raspberrypi/rp2040/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
tinyusb/src/portable/raspberrypi/rp2040/%.o: ../tinyusb/src/portable/raspberrypi/rp2040/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -ffreestanding -Wunused -Wuninitialized -g -I"/home/harry/mounriver-studio-projects/CH32MK/Debug" -I"/home/harry/mounriver-studio-projects/CH32MK/Core" -I"/home/harry/mounriver-studio-projects/CH32MK/User" -I"/home/harry/mounriver-studio-projects/CH32MK/Peripheral/inc" -I"/home/harry/mounriver-studio-projects/CH32MK/tinyusb" -I"/home/harry/mounriver-studio-projects/CH32MK/tinyusb/src" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/usb" -I"/home/harry/mounriver-studio-projects/CH32MK/User/config" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/gpio" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/matrix" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/debounce" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/keycodes" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/split" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/systick" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/layers" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/process_keymap" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

