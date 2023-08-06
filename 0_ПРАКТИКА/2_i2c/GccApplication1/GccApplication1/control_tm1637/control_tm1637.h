#ifndef CONTROL_TM1637_H_
#define CONTROL_TM1637_H_
#define NO_WORD ((uint8_t) {H_RUS, E_RUS, A_RUS})
void wakeup_display();
void print_time_on_display(uint8_t hour, uint8_t min);

#endif