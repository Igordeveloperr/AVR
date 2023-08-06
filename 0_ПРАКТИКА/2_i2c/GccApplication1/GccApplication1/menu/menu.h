#ifndef MENU_H_
#define MENU_H_
#define WAIT1S 1000
#define WAIT500MS 500
#define MAX_WAIT_TIME 8
#define MENU_BTN PD4
#define UP_BTN PD5
#define DOWN_BTN PD6
#define VIEW_BTN PD7
#define UP_BTN_CLICK (~PIND & (1 << UP_BTN))
#define DOWN_BTN_CLICK (~PIND & (1 << DOWN_BTN))
#define MENU_BTN_CLICK (~PIND & (1 << MENU_BTN))
#define VIEW_BTN_CLICK (~PIND & (1 << VIEW_BTN))

void event_listener();
void setup_time(uint8_t* seconds, uint8_t* minutes, uint8_t* hour);

#endif