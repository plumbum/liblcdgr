#*****************************************************************

#  Makefile 
#
#  Based on Makefile from scmRTOS GCC port
#  Modified by Ivan A-R <ivan@tuxotronic.org>
#
#*****************************************************************

# vim: sw=8:ts=8:si:noexpandtab

#TOOLSET = 
TOOLSET = /usr/local/arm/arm-2008q3/bin/

TARGET = arm-none-eabi-
#TARGET = arm-elf-

PATH=$(TOOLSET):/usr/bin:/bin:/usr/local/bin


CC   = $(TARGET)gcc
CXX  = $(TARGET)g++
AS   = $(TARGET)gcc -x assembler-with-cpp
LD   = $(TARGET)g++
GDB  = $(TARGET)gdb
OBJCOPY = $(TARGET)objcopy
OBJDUMP = $(TARGET)objdump 
SIZE = $(TARGET)size 

RM = rm -f


CHIP = STM32F10x

MEM = ROM
#MEM = RAM

PROJECT = demo_prj

OPTIMIZE = -Os

##############################################################################################
# Application sources directories
SRC_DIRS = ./src
#SRC_DIRS += ./stm32_lib/STM32F10x_StdPeriph_Driver/src
SRC_DIRS += ./sys_src
SRC_DIRS += ./sys_src/startup
SRC_DIRS += ../lib

# Directories to search includes
INC_DIRS = ./inc
INC_DIRS += ./src
INC_DIRS += ./stm32_lib/STM32F10x_StdPeriph_Driver/inc
INC_DIRS += ./sys_src
INC_DIRS += ../lib


# Directory ld script
LD_DIRS = ./ldscripts
LIB_DIRS += $(LD_DIRS)

##############################################################################################
#  ARM .c sources

SRC_ARM_C = main.c
SRC_ARM_C += lcd.c
SRC_ARM_C += stm32f10x_it.c

####################
# CMSIS components
SRC_ARM_C += core_cm3.c
SRC_ARM_C += system_stm32f10x.c
#SRC_ARM_C += startup_stm32f10x_ld.c
SRC_ARM_C += startup_stm32f10x_md.c
#SRC_ARM_C += startup_stm32f10x_hd.c

# ST Periph library components
#SRC_ARM_C += misc.c
#SRC_ARM_C += stm32f10x_adc.c
#SRC_ARM_C += stm32f10x_bkp.c
#SRC_ARM_C += stm32f10x_can.c
#SRC_ARM_C += stm32f10x_crc.c
#SRC_ARM_C += stm32f10x_dac.c
#SRC_ARM_C += stm32f10x_dbgmcu.c
#SRC_ARM_C += stm32f10x_dma.c
#SRC_ARM_C += stm32f10x_exti.c
#SRC_ARM_C += stm32f10x_flash.c
#SRC_ARM_C += stm32f10x_fsmc.c
#SRC_ARM_C += stm32f10x_gpio.c
#SRC_ARM_C += stm32f10x_i2c.c
#SRC_ARM_C += stm32f10x_iwdg.c
#SRC_ARM_C += stm32f10x_pwr.c
#SRC_ARM_C += stm32f10x_rcc.c
#SRC_ARM_C += stm32f10x_rtc.c
#SRC_ARM_C += stm32f10x_sdio.c
#SRC_ARM_C += stm32f10x_spi.c
#SRC_ARM_C += stm32f10x_tim.c
#SRC_ARM_C += stm32f10x_usart.c
#SRC_ARM_C += stm32f10x_wwdg.c


############################
#  ARM .cpp sources
SRC_ARM_CPP =

############################
#  ARM .s sources
SRC_ARM_ASM =
#SRC_ARM_ASM += crt.s

############################
# libraries
LIBS =

##############################################################################################
LD_SCRIPT= $(LD_DIRS)/$(CHIP)_$(MEM).ld

##############################################################################################
# predefined symbols for all sources
#DEFS = -DUSE_FULL_ASSERT=1    
DEFS =
# predefined symbols for .c sources
C_DEFS = 
# predefined symbols for .cpp sources
CPP_DEFS = 
# predefined symbols for .s sources
ASM_DEFS = 

##############################################################################################
# Output files
ELF = $(BINDIR)/$(PROJECT).elf
HEX = $(BINDIR)/$(PROJECT).hex
BIN = $(BINDIR)/$(PROJECT).bin
LSS = $(LSTDIR)/$(PROJECT).lss
##############################################################################################
##############################################################################################
FMCU  = -mcpu=cortex-m3 -mthumb

INC_DIRS += $(scmRTOS_DIRS)
INC_DIRS += $(SRC_DIRS)

OBJDIR := ./obj
LSTDIR := ./list
BINDIR := ./bin
DEPDIR := $(OBJDIR)/.dep
#-----------------------------------------------
#    add surce files directories to search path
vpath
vpath % $(scmRTOS_DIRS)
vpath % $(SRC_DIRS)
vpath % $(LIB_DIRS)/src

OBJS_ARM_ASM  = $(addprefix $(OBJDIR)/,$(notdir $(SRC_ARM_ASM:.s=.o) ))
OBJS_ARM_C  = $(addprefix $(OBJDIR)/,$(notdir $(SRC_ARM_C:.c=.o) ))
OBJS_ARM_CPP  = $(addprefix $(OBJDIR)/,$(notdir $(SRC_ARM_CPP:.cpp=.o) ))
#OBJS_THUMB_ASM  = $(addprefix $(OBJDIR)/,$(notdir $(SRC_THUMB_ASM:.s=.o) ))
#OBJS_THUMB_CPP  = $(addprefix $(OBJDIR)/,$(notdir $(SRC_THUMB_CPP:.cpp=.o) ))
OBJS = $(OBJS_ARM_CPP) $(OBJS_ARM_C) $(OBJS_ARM_ASM) $(OBJS_THUMB_CPP) $(OBJS_THUMB_ASM)

# defines
DEFS += -D$(CHIP)=1
C_DEFS += $(DEFS)
CPP_DEFS += $(DEFS)
ASM_DEFS += $(DEFS)
# Flags

FLAGS = $(FMCU)
# generate debug info in dwarf-2 format
FLAGS += -g -gdwarf-2
# generate dependency info  
FLAGS += -MD -MP -MF $(DEPDIR)/$(@F).d
# include search path
FLAGS += $(addprefix -I,$(INC_DIRS))

#if any THUMB mode sources, generate interworking code
#ifneq ($(strip $(SRC_THUMB_ASM) $(SRC_THUMB_CPP)),)
#FLAGS += -mthumb-interwork
#endif

ASM_FLAGS = $(FLAGS)
ASM_FLAGS += $(ASM_DEFS)
ASM_FLAGS += -Wa,-amhlds=$(LSTDIR)/$(notdir $(<:.s=.lst)) 

C_FLAGS = $(FLAGS)
C_FLAGS += $(OPTIMIZE)
C_FLAGS += $(CPP_DEFS)
C_FLAGS += -fomit-frame-pointer
C_FLAGS += -fno-exceptions
C_FLAGS += -Wall -Wextra -Wundef -Wcast-align
C_FLAGS += -Wa,-ahlmsdc=$(LSTDIR)/$(notdir $(<:.c=.lst)) -fverbose-asm
C_FLAGS += -ffunction-sections -fdata-sections    # to remove dead code, if any, at link time
C_FLAGS += -finline-limit=20             # generate warning if inlinign fails
#C_FLAGS += -Winline -finline-limit=32             # generate warning if inlinign fails
C_FLAGS += -funsigned-bitfields -fshort-enums	  # actually not important for scmRTOS

CPP_FLAGS = $(FLAGS)
CPP_FLAGS += $(OPTIMIZE)
CPP_FLAGS += $(CPP_DEFS)
CPP_FLAGS += -fomit-frame-pointer
CPP_FLAGS += -fno-exceptions -fno-rtti
CPP_FLAGS += -Wall -Wextra -Wundef -Wcast-align
CPP_FLAGS += -Weffc++ -fno-elide-constructors -Wctor-dtor-privacy
CPP_FLAGS += -Wa,-ahlmsdc=$(LSTDIR)/$(notdir $(<:.cpp=.lst)) -fverbose-asm
CPP_FLAGS += -ffunction-sections -fdata-sections    # to remove dead code, if any, at link time
CPP_FLAGS += -Winline -finline-limit=10             # generate warning if inlinign fails
CPP_FLAGS += -funsigned-bitfields -fshort-enums	    # actually not important for scmRTOS


LD_FLAGS = $(FMCU)
LD_FLAGS += -nostartfiles
LD_FLAGS += -T$(LD_SCRIPT)
LD_FLAGS += -Wl,-Map=$(LSTDIR)/$(PROJECT).map,--cref,--no-warn-mismatch
LD_FLAGS += $(addprefix -L,$(LIB_DIRS))
LD_FLAGS += $(LIBDIR)
LD_FLAGS += -Wl,--gc-sections
# LD_FLAGS += -Wl,--defsym,__dso_handle=0


#
# makefile rules
#

.SILENT :
.PHONY : all clean load debug tags

all: directories $(OBJS) $(ELF)  $(LSS) size $(HEX) $(BIN)
#all: directories $(OBJS) $(ELF) $(LSS) size

#all objects depends on makefile
$(OBJS): Makefile

$(OBJS_ARM_C) : $(OBJDIR)/%.o : %.c
	@echo Compiling: $<
	$(CC) -c $(C_FLAGS) $< -o $@

$(OBJS_ARM_CPP) : $(OBJDIR)/%.o : %.cpp
	@echo Compiling: $<
	$(CXX) -c $(CPP_FLAGS) $< -o $@

$(OBJS_ARM_ASM) : $(OBJDIR)/%.o : %.s
	@echo Assembling: $<
	$(AS) -c $(ASM_FLAGS) $< -o $@

#$(OBJS_THUMB_CPP) : $(OBJDIR)/%.o : %.cpp
#	@echo Compiling: $<
#	$(CC) -c -mthumb $(CPP_FLAGS) $< -o $@

#$(OBJS_THUMB_ASM) : $(OBJDIR)/%.o : %.s
#	@echo Assembling: $<
#	$(AS) -c  -mthumb $(ASM_FLAGS) $< -o $@

$(ELF): $(OBJS) $(LD_SCRIPT)
	@echo Linking: $@
	$(LD) $(OBJS) $(LD_FLAGS) $(LIBS) -o $@

$(LSS): $(ELF)
	$(OBJDUMP) -h -S -C $< > $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

size:
	$(SIZE) -B -t $(ELF)
	$(SIZE) -A -t $(ELF)

directories:
	mkdir -p $(BINDIR) $(OBJDIR) $(DEPDIR) $(LSTDIR)

clean:
	$(RM) -r $(BINDIR) $(OBJDIR) $(DEPDIR) $(LSTDIR)

load: $(BIN)
	python utils/stm32loader.py -e -w -v $<
#	~/Projects/cortex/loader/stm32loader.py -p /dev/ttyS1 -e -w -v $<
    
debug: $(ELF)
	$(GDB) -x debug.gdb $<

tags:
	ctags -R --c++-kinds=+p --fields=+iaS --extra=+q ..

# set TOOLSET bin directory first in PATH    
ifeq (,$(findstring ;,$(PATH)))
  PATH := $(subst :,,/$(TOOLSET)/bin):$(PATH)
else
  PATH := $(subst /,\,$(TOOLSET)/bin);$(PATH)
endif
export PATH

# dependencies inclusion
# if make target list not contain this targets - include dependencies
ifeq (,$(findstring clean,$(MAKECMDGOALS)))
 ifeq (,$(findstring directories,$(MAKECMDGOALS)))
-include $(shell mkdir $(DEPDIR) 2>/dev/null) $(wildcard $(DEPDIR)/*.d)
 endif
endif

