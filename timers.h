#ifndef TIMERS_H
#define TIMERS_H

//general timer functions
void TIMERS_init_async_timer(void);
void TIMERS_init_io_timer(void);

void TIMERS_start_async_timer(char timer);
void TIMERS_stop_async_timer(void);

void TIMERS_start_io_timer(char timer, char ctc);
void TIMERS_stop_io_timer(void);
int  TIMERS_get_io_count(void);
void TIMERS_set_io_compare(short int  comp);

//calibration functions
void TIMERS_calibrate_io_osc(int target_ticks, int threshold);
char TIMERS_calibrating(void);
unsigned long int TIMERS_get_current_freq(void);

//device mode functions
void TIMERS_set_mode(short int mode);
char TIMERS_get_mode(void);

//pwm functions
int TIMERS_get_tmr_count(void);
void TIMERS_set_tmr_max(int max);

#endif
