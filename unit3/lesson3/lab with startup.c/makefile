CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m3 -mthumb -gdwarf-2
INCS=-I .
LIBS=
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
AS = $(wildcard *.s)
ASOBJ = $(AS:.s=.o)
project_name=learn-in-depth-cortex-m3

all: $(project_name).bin
	@echo "build is done"

%.o: %.c
	$(CC)gcc -c $(INCS) $(CFLAGS) $< -o $@


$(project_name).elf: $(OBJ) $(ASOBJ)
	$(CC)ld -T linker_script.ld -Map=map.out $(LIBS) $(OBJ) $(ASOBJ) -o $@ -Map=map.out

$(project_name).bin: $(project_name).elf
	$(CC)objcopy -O binary $< $@

clean_all:
	rm -f *.o *.bin *.elf

clean:
	rm -f *.bin *.elf