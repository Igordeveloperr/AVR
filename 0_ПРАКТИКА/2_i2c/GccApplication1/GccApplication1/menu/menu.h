#ifndef MENU_H_
#define MENU_H_
#define ON 1
#define OFF 0
#define WAIT 500
#define MAX_WAIT_TIME 4

void event_listener();
void setup_time(uint8_t* seconds, uint8_t* minutes, uint8_t* hour);

#endif