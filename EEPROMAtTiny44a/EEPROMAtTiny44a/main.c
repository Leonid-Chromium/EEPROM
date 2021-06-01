/*
 * EEPROMAtTiny44a.c
 *
 * Created: 27.05.2021 9:37:50
 * Author : Leo
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>

#define F_CPU 1000000 UL;

int main(void)
{
	//Порт А0 пин 13 на вход
	DDRA = 0b00000000;
	//Настраиваем АЦП
	ADMUX=
	(1<<MUX0)|
	(0<<MUX1)|
	(0<<MUX2)|
	(0<<MUX3)|
	(0<<MUX4)|
	(0<<MUX5)| //выбираем ADC1 для ввода через мультиплексер
	(0<<REFS0)|
	(0<<REFS1); //вибираем внешний источник
	ADCSRB=
	(0<<BIN)|
	(0<<ACME)|
	(1<<ADLAR)| //выравнивание справо
	(0<<ADTS0)|
	(0<<ADTS1)|
	(0<<ADTS2);
	
	ADCSRA|=
	(1<<ADEN)| //разрешаем работу АЦП
	(1<<ADPS2)| 
	(0<<ADPS1)|
	(0<<ADPS0)|//Устанавливаем прескейлер на 4
	(1<<ADATE)|
	(0<<ADIE);
	DIDR0=0xff;
	// Запуск АЦП
	ADCSRA|=(1<<ADSC);
	
	//настройка пределителя тактовой частоты контроллера
	//CLKPR = 128;
	//CLKPR = 4;
	
	//настройка всех портов на выход
	DDRB = 0b11111111;
	//настройка таймера
	TCCR0A = 0b10000011;
	TCCR0B = 0b00000010;
	OCR0A=eeprom_read_byte(0);
	
	while (1)
	{
		//изменение точки скважности
		ADCSRA|=(1<<ADSC);
		_delay_ms(10);
		OCR0A=ADCH;
		eeprom_update_byte(0,ADCH);
	}
}