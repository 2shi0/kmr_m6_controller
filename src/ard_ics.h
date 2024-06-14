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
  ard_ics(uint8_t tx_pin);
  void set_pos(unsigned char id, int pos);
  void set_motion();
  void set_speed(unsigned char speed);

private:
  unsigned char tx[3];
  int filter_sitting_height_neutral[NUM_OF_SERVO] = {1, 0, -1, 0, 1, 0, -1, 0, 1, 0, -1, 0};
  int filter_leg_opening_neutral[NUM_OF_SERVO] = {0, -1, 0, 1, 0, 0, 0, -0, 0, 1, 0, -1};

  int filter_leg_up_1[NUM_OF_SERVO] = {-1, 0, 0, 0,
                                       0, 0, 1, 0,
                                       -1, 0, 0, 0};
  int filter_leg_up_2[NUM_OF_SERVO] = {0, 0, 1, 0,
                                       -1, 0, 0, 0,
                                       0, 0, 1, 0};
  int filter_leg_forward_1[NUM_OF_SERVO] = {0, 1, 0, 0,
                                            0, 0, 0, -1,
                                            0, 1, 0, 0};
  int filter_leg_forward_2[NUM_OF_SERVO] = {0, 0, 0, -1,
                                            0, 1, 0, 0,
                                            0, 0, 0, -1};
};

#endif