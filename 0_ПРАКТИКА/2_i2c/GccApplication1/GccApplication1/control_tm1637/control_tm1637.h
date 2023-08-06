#ifndef CONTROL_TM1637_H_
#define CONTROL_TM1637_H_
#define HI_WORD ((uint8_t[]) {TM1637_SPAT_H, TM1637_SPAT_o, TM1637_SPAT_L, TM1637_SPAT_A})
#define SET_WORD ((uint8_t[]) {TM1637_SPAT_S, TM1637_SPAT_e, TM1637_SPAT_t, TM1637_SPAT_t})
#define DONE_WORD ((uint8_t[]) {TM1637_SPAT_d, TM1637_SPAT_o, TM1637_SPAT_n, TM1637_SPAT_E})
#define EAT_WORD ((uint8_t[]) {TM1637_SPAT_E, TM1637_SPAT_A, TM1637_SPAT_t, TM1637_SPAT_HAPPY})
void wakeup_display();
void print_time_on_display(uint8_t hour, uint8_t min);

#endif