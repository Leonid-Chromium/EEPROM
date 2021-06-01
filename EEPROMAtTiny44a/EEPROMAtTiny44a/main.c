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
	//���� �0 ��� 13 �� ����
	DDRA = 0b00000000;
	//����������� ���
	ADMUX=
	(1<<MUX0)|
	(0<<MUX1)|
	(0<<MUX2)|
	(0<<MUX3)|
	(0<<MUX4)|
	(0<<MUX5)| //�������� ADC1 ��� ����� ����� �������������
	(0<<REFS0)|
	(0<<REFS1); //�������� ������� ��������
	ADCSRB=
	(0<<BIN)|
	(0<<ACME)|
	(1<<ADLAR)| //������������ ������
	(0<<ADTS0)|
	(0<<ADTS1)|
	(0<<ADTS2);
	
	ADCSRA|=
	(1<<ADEN)| //��������� ������ ���
	(1<<ADPS2)| 
	(0<<ADPS1)|
	(0<<ADPS0)|//������������� ���������� �� 4
	(1<<ADATE)|
	(0<<ADIE);
	DIDR0=0xff;
	// ������ ���
	ADCSRA|=(1<<ADSC);
	
	//��������� ����������� �������� ������� �����������
	//CLKPR = 128;
	//CLKPR = 4;
	
	//��������� ���� ������ �� �����
	DDRB = 0b11111111;
	//��������� �������
	TCCR0A = 0b10000011;
	TCCR0B = 0b00000010;
	OCR0A=eeprom_read_byte(0);
	
	while (1)
	{
		//��������� ����� ����������
		ADCSRA|=(1<<ADSC);
		_delay_ms(10);
		OCR0A=ADCH;
		eeprom_update_byte(0,ADCH);
	}
}