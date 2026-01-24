all:image

i2c.o:I2C/I2C_Main.c
	avr-gcc -mmcu=atmega328p -c -Wextra -Wall -Os -o obj/i2c.o I2C/I2C_Main.c

rtc.o:RTC/RTC_Main.c
	avr-gcc -mmcu=atmega328p -c -Wextra -Wall -Os -o obj/rtc.o RTC/RTC_Main.c

lcd.o:LCD/lcd.c
	avr-gcc -mmcu=atmega328p -c -Wextra -Wall -Os -o obj/lcd.o LCD/LCD.c

main.o:main.c
	avr-gcc -mmcu=atmega328p -c -Wextra -Wall -Os -o obj/main.o main.c

image:i2c.o rtc.o lcd.o main.o
	avr-gcc -mmcu=atmega328p -Wextra -Wall -Os -o out/image.elf obj/main.o obj/lcd.o obj/i2c.o obj/rtc.o
	avr-objcopy -j .text -j .data -O ihex out/image.elf out/image.hex
	avr-size out/image.elf
	
flash:
	avrdude -c usbasp -p atmega328p -U flash:w:out/image.hex

clean:
	rm out/image.elf
	rm out/image.hex
	rm obj/main.o
	rm obj/lcd.o
	rm obj/i2c.o
	rm obj/rtc.o
