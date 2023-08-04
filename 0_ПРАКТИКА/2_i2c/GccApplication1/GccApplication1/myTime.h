#ifndef MYTIME_H_
#define MYTIME_H_

void control_seconds(uint8_t* seconds, uint8_t* minutes);
void control_min(uint8_t* minutes, uint8_t* hour);
void control_hour(uint8_t* seconds, uint8_t* minutes, uint8_t* hour);

#endif /* MYTIME_H_ */