################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../usbdrv \
../Irmp


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../usbdrv/oddebug.c \
../usbdrv/usbdrv.c \
../Irmp/irmp.c \
../main.c


PREPROCESSING_SRCS +=  \
../usbdrv/usbdrvasm.S


ASM_SRCS += 


OBJS +=  \
usbdrv/oddebug.o \
usbdrv/usbdrvasm.o \
usbdrv/usbdrv.o \
Irmp/irmp.o \
main.o


OBJS_AS_ARGS +=  \
usbdrv/oddebug.o \
usbdrv/usbdrvasm.o \
usbdrv/usbdrv.o \
Irmp/irmp.o \
main.o


C_DEPS +=  \
usbdrv/oddebug.d \
usbdrv/usbdrv.d \
Irmp/irmp.d \
main.d


C_DEPS_AS_ARGS +=  \
usbdrv/oddebug.d \
usbdrv/usbdrv.d \
Irmp/irmp.d \
main.d


OUTPUT_FILE_PATH +=USB_IR_Remote_Receiver.elf

OUTPUT_FILE_PATH_AS_ARGS +=USB_IR_Remote_Receiver.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

# AVR32/GNU C Compiler









usbdrv/%.o: ../usbdrv/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler
	$(QUOTE)C:\Program Files (x86)\Atmel\AVR Studio 5.1\extensions\Atmel\AVRGCC\3.3.1\AVRToolchain\bin\avr-gcc.exe$(QUOTE)  -funsigned-char -funsigned-bitfields -DF_CPU=12000000UL  -I"..\." -I"..\usbdrv"  -Os -fpack-struct -fshort-enums -Wall -c -gdwarf-2 -std=gnu99  -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -mmcu=atmega8  -o"$@" "$<" 
	@echo Finished building: $<

Irmp/%.o: ../Irmp/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler
	$(QUOTE)C:\Program Files (x86)\Atmel\AVR Studio 5.1\extensions\Atmel\AVRGCC\3.3.1\AVRToolchain\bin\avr-gcc.exe$(QUOTE)  -funsigned-char -funsigned-bitfields -DF_CPU=12000000UL  -I"..\." -I"..\usbdrv"  -Os -fpack-struct -fshort-enums -Wall -c -gdwarf-2 -std=gnu99  -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -mmcu=atmega8  -o"$@" "$<" 
	@echo Finished building: $<

./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler
	$(QUOTE)C:\Program Files (x86)\Atmel\AVR Studio 5.1\extensions\Atmel\AVRGCC\3.3.1\AVRToolchain\bin\avr-gcc.exe$(QUOTE)  -funsigned-char -funsigned-bitfields -DF_CPU=12000000UL  -I"..\." -I"..\usbdrv"  -Os -fpack-struct -fshort-enums -Wall -c -gdwarf-2 -std=gnu99  -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -mmcu=atmega8  -o"$@" "$<" 
	@echo Finished building: $<



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler
usbdrv/usbdrvasm.o: ../usbdrv/usbdrvasm.s
	@echo Building file: $<
	@echo Invoking: AVR32/GNU C Assembler
	$(QUOTE)C:\Program Files (x86)\Atmel\AVR Studio 5.1\extensions\Atmel\AVRGCC\3.3.1\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -Wa,-gdwarf2 -x assembler-with-cpp -c -Wall -gdwarf-2 -std=gnu99 -DF_CPU=12000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -I "..\." -I "..\usbdrv"   -mmcu=atmega8   -o"$@" "$<"
	@echo Finished building: $<


usbdrv/%.o: ../usbdrv/%.s
	@echo Building file: $<
	@echo Invoking: AVR32/GNU C Assembler
	$(QUOTE)C:\Program Files (x86)\Atmel\AVR Studio 5.1\extensions\Atmel\AVRGCC\3.3.1\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -Wa,-gdwarf2 -x assembler-with-cpp -c -Wall -gdwarf-2 -std=gnu99 -DF_CPU=12000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -I "..\." -I "..\usbdrv"   -mmcu=atmega8   -o"$@" "$<"
	@echo Finished building: $<




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU C Linker
	$(QUOTE)C:\Program Files (x86)\Atmel\AVR Studio 5.1\extensions\Atmel\AVRGCC\3.3.1\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="USB_IR_Remote_Receiver.map"  -mmcu=atmega8  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\AVR Studio 5.1\extensions\Atmel\AVRGCC\3.3.1\AVRToolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "USB_IR_Remote_Receiver.elf" "USB_IR_Remote_Receiver.hex"
	"C:\Program Files (x86)\Atmel\AVR Studio 5.1\extensions\Atmel\AVRGCC\3.3.1\AVRToolchain\bin\avr-objcopy.exe" -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex "USB_IR_Remote_Receiver.elf" "USB_IR_Remote_Receiver.eep" || exit -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex "USB_IR_Remote_Receiver.elf" "USB_IR_Remote_Receiver.eep" || exit 0
	"C:\Program Files (x86)\Atmel\AVR Studio 5.1\extensions\Atmel\AVRGCC\3.3.1\AVRToolchain\bin\avr-objdump.exe" -h -S "USB_IR_Remote_Receiver.elf" > "USB_IR_Remote_Receiver.lss"
	"C:\Program Files (x86)\Atmel\AVR Studio 5.1\extensions\Atmel\AVRGCC\3.3.1\AVRToolchain\bin\avr-size.exe" -C --mcu=atmega8  "USB_IR_Remote_Receiver.elf"
	




# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) 
	rm -rf "USB_IR_Remote_Receiver.hex" "USB_IR_Remote_Receiver.lss" "USB_IR_Remote_Receiver.eep" "USB_IR_Remote_Receiver.map"
	