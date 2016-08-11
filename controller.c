#include "global.h"
#include "uart.h"
#include "timers.h"
#include "pins.h"
#include "pwm.h"
#include <stdio.h>
 
int i;
short int mode = 2;
unsigned long int cpu_freq = 1000000;
unsigned long int BAUDRATE = 19200;


int  main()
{
  sei();                                        //enable global interrupts
  
  LED(1);                                       /* turn led on */
  cpu_freq = TIMERS_get_current_freq();         /* get the cpu frequency, found from xtal/timers */

  USART_init(BAUDRATE, F_CPU);                  //init usart
  PINS_init();

  TIMERS_init_async_timer();                    /* init timers */

  TIMERS_init_io_timer();
  /* TIMERS_set_tmr_max(255); */
  TIMERS_start_io_timer(1,0);

  mode = 2;

  while(1){
  /*-----------------------------------------------------------------------------
   *  uart echo block
   *-----------------------------------------------------------------------------*/
    if (USART_need_rx_update()){                //a string has been recieved, update the things
      USART_unset_rxb_update();
      USART_copy_rxb();

      //print the recieved message
      USART_putstring(USART_get_last_message()); /* transmit the last recieved message (uart echo) */

      //delay while tx completes to print newline
      //WARNING: this is blocking, for testing onlm
      //must be removed when implementation of 
      //timing sensitive content in main loop added
      while (USART_get_tx_status()){
        _delay_ms(10);
      }

      USART_putstring("\r\n");
    }

    switch(mode){
      /*-----------------------------------------------------------------------------
       *  normal mode, just blink the led
       *-----------------------------------------------------------------------------*/
      case 0:
        _delay_ms(1000);
        if (readLED){
          LED(0);
          /* PWM_set_half_pwm(20, 10, 0); /1* ALI1 *1/ */
        }
        else{
          LED(1);
          /* setPin(PORTB, 4, 1); */
          /* PWM_set_half_pwm(10, 20, 0); /1* ALI1 *1/ */
        }
        break;

      /*-----------------------------------------------------------------------------
       *  Calibration mode, at this point do nothing
       *-----------------------------------------------------------------------------*/
      case 1:
        break;

      /*-----------------------------------------------------------------------------
       *  half swing PWM mode
       *-----------------------------------------------------------------------------*/
      case 2:
        TIMERS_set_io_compare(16383,0);

        break;
    }
  }
}

