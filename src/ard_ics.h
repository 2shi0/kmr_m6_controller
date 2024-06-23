#ifndef _ARD_ICS_h
#define _ARD_ICS_h

#include <Arduino.h>
#include "task_maker.h"

#define MOTION_HOME 0
#define MOTION_FORWORD 1
#define MOTION_BACK 2

#define NUM_OF_SERVO 12

class ard_ics : public task_maker
{
public:
  ard_ics(uint8_t tx_pin, unsigned char speed);
  void set_pos(unsigned char id, int pos);
  void task();
  char latest_rx = 'z';

private:
  unsigned char tx[3];
};

#endif