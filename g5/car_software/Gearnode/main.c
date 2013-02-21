/*********************************************
 * Unicorn main gear kontrol
 *********************************************/
/*
-Gear Servo styres gennem PE5 PWM
-Maaler Position paa gear aktuater gennem ADC (ADC1)
-Timer overflow (TIMER0_OVF_vect) styrer opdateringen af signal til aktuator (~170 Hz)
-Signal fra gearkontakter, kommer fra node 2 over CAN
*/
#include "config.h"
#include "extern.h"
#include "prototyper.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "can_std/can_lib.h"
#include "can_new.h"
#include "../lib/can_defs.h"
#include "../lib/data_def.h"


extern unsigned int GearEst_val;
unsigned int pos = 0;


int main(void)
{
	_delay_ms(500);
	uint8_t data_buf[8];
	ioinit();
	uartinit();
	can_init(0);
    pwm16Init2();
	adcInit(1);
	st_cmd_t rpm_msg;
	counter0Init();

	_delay_ms(500);
	sei();
    
	sendtekst("\n\rUnicorn Gearnode v1.0 \n\r");

	//rpm_msg.pt_data = rpm_response_buffer;
	//rpm_msg.status = 0;

	//can_update_rx_msg(&rpm_msg, rpm_msgid, 8);
	//can_update_rx_msg(&rpm_msg, gear_msgid, 8);

	Can_sei();
	Can_set_tx_int();
	Can_set_rx_int();
    
    //Full turn time: ~700 ms
    int time = 2000;
	while(1)
	{
		//_delay_ms(100);
		//data_buf[0] = GearNeutral;
		//data_buf[1] = GEARNEUTRALMEAS;
		//data_buf[2] = 0;
		//can_send_non_blocking(rpm_msgid, data_buf, 3);

		//data_buf[0] = GearEst;
		//data_buf[1] = 0;
		//data_buf[2] = GearEst_val;
		//can_send_non_blocking(rpm_msgid, data_buf, 3);
        _delay_ms(2000);
        servoPosition(TOPPOS);
        _delay_ms(2000);
        servoPosition(MIDPOS);
        _delay_ms(2000);
        servoPosition(BUTPOS);
        
	}
    return 0;
}
