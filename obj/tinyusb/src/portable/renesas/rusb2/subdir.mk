################################################################################
# MRS Version: 2.5.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tinyusb/src/portable/renesas/rusb2/dcd_rusb2.c \
../tinyusb/src/portable/renesas/rusb2/hcd_rusb2.c \
../tinyusb/src/portable/renesas/rusb2/rusb2_common.c 

C_DEPS += \
./tinyusb/src/portable/renesas/rusb2/dcd_rusb2.d \
./tinyusb/src/portable/renesas/rusb2/hcd_rusb2.d \
./tinyusb/src/portable/renesas/rusb2/rusb2_common.d 

OBJS += \
./tinyusb/src/portable/renesas/rusb2/dcd_rusb2.o \
./tinyusb/src/portable/renesas/rusb2/hcd_rusb2.o \
./tinyusb/src/portable/renesas/rusb2/rusb2_common.o 

DIR_OBJS += \
./tinyusb/src/portable/renesas/rusb2/*.o \

DIR_DEPS += \
./tinyusb/src/portable/renesas/rusb2/*.d \

DIR_EXPANDS += \
./tinyusb/src/portable/renesas/rusb2/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
tinyusb/src/portable/renesas/rusb2/%.o: ../tinyusb/src/portable/renesas/rusb2/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -ffreestanding -Wunused -Wuninitialized -g -I"/home/harry/mounriver-studio-projects/CH32MK/Debug" -I"/home/harry/mounriver-studio-projects/CH32MK/Core" -I"/home/harry/mounriver-studio-projects/CH32MK/User" -I"/home/harry/mounriver-studio-projects/CH32MK/Peripheral/inc" -I"/home/harry/mounriver-studio-projects/CH32MK/tinyusb" -I"/home/harry/mounriver-studio-projects/CH32MK/tinyusb/src" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/usb" -I"/home/harry/mounriver-studio-projects/CH32MK/User/config" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/gpio" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/matrix" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/debounce" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/keycodes" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/split" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/systick" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/layers" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/process_keymap" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

