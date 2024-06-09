#ifndef _ARD_ICS_h
#define _ARD_ICS_h

#include <Arduino.h>

class ard_ics {
public:
  ard_ics(int tx_pin);
  void set_pos(unsigned char id, int pos);

private:
  unsigned char tx[3];
};

#endif