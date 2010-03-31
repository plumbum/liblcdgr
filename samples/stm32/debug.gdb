target remote :3333

monitor reset halt

monitor flash probe 0

monitor stm32x unlock 0
monitor stm32x mass_erase 0

#monitor flash write_image ../main.hex 0 ihex

load

monitor reset halt


