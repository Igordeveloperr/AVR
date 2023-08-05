#ifndef MENU_H_
#define MENU_H_
#define WAIT 500
#define MAX_WAIT_TIME 8
#define UP_BTN_CLICK (!(PIND & (1 << UP_BTN)))
#define DOWN_BTN_CLICK (!(PIND & (1 << DOWN_BTN)))
#define MENU_BTN_CLICK (!(PIND & (1 << MENU_BTN)))

void event_listener();
void setup_time(uint8_t* seconds, uint8_t* minutes, uint8_t* hour);

#endif