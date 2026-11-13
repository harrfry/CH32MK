################################################################################
# MRS Version: 2.5.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tinyusb/src/portable/st/stm32_fsdev/dcd_stm32_fsdev.c \
../tinyusb/src/portable/st/stm32_fsdev/fsdev_common.c \
../tinyusb/src/portable/st/stm32_fsdev/hcd_stm32_fsdev.c 

C_DEPS += \
./tinyusb/src/portable/st/stm32_fsdev/dcd_stm32_fsdev.d \
./tinyusb/src/portable/st/stm32_fsdev/fsdev_common.d \
./tinyusb/src/portable/st/stm32_fsdev/hcd_stm32_fsdev.d 

OBJS += \
./tinyusb/src/portable/st/stm32_fsdev/dcd_stm32_fsdev.o \
./tinyusb/src/portable/st/stm32_fsdev/fsdev_common.o \
./tinyusb/src/portable/st/stm32_fsdev/hcd_stm32_fsdev.o 

DIR_OBJS += \
./tinyusb/src/portable/st/stm32_fsdev/*.o \

DIR_DEPS += \
./tinyusb/src/portable/st/stm32_fsdev/*.d \

DIR_EXPANDS += \
./tinyusb/src/portable/st/stm32_fsdev/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
tinyusb/src/portable/st/stm32_fsdev/%.o: ../tinyusb/src/portable/st/stm32_fsdev/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -ffreestanding -Wunused -Wuninitialized -g -I"/home/harry/mounriver-studio-projects/CH32MK/Debug" -I"/home/harry/mounriver-studio-projects/CH32MK/Core" -I"/home/harry/mounriver-studio-projects/CH32MK/User" -I"/home/harry/mounriver-studio-projects/CH32MK/Peripheral/inc" -I"/home/harry/mounriver-studio-projects/CH32MK/tinyusb" -I"/home/harry/mounriver-studio-projects/CH32MK/tinyusb/src" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/usb" -I"/home/harry/mounriver-studio-projects/CH32MK/User/config" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/gpio" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/matrix" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/debounce" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/keycodes" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/split" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/systick" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/layers" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/process_keymap" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/events" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/process_matrix" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/engine" -I"/home/harry/mounriver-studio-projects/CH32MK/User/drivers/engine/tap-hold" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

