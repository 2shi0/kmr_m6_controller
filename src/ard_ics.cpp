#include "ard_ics.h"

ard_ics::ard_ics(uint8_t tx_pin)
{
  Serial1.begin(115200, SERIAL_8E1, -1, tx_pin);
  while (!Serial1)
    delay(1);
}

void ard_ics::set_pos(unsigned char id, int pos)
{
  id = constrain(id, 0, 31);
  pos = constrain(pos + 7500, 3500, 11500);

  tx[0] = 0x80 | id;
  tx[1] = (unsigned char)(pos >> 7 & 0x7F);
  tx[2] = (unsigned char)(pos & 0x7F);

  for (unsigned char i : tx)
  {
    Serial1.write(i);
  }
}

void ard_ics::set_speed(unsigned char speed)
{
  tx[1] = 0x02;
  tx[2] = constrain(speed, 0, 127);
  for (unsigned char i = 0; i < 12; i++)
  {
    tx[0] = 0xC0 | i;
    for (unsigned char i : tx)
    {
      Serial1.write(i);
    }
  }
  delay(100);
}

void ard_ics::set_motion()
{

  for (unsigned char i = 0; i < NUM_OF_SERVO; i++)
  {
    set_pos(i, filter_sitting_height_neutral[i] * 800 + filter_leg_opening_neutral[i] * 400);
  }

  delay(1000);

  /* 足踏み
  while (1)
  {
    for (unsigned char i = 0; i < NUM_OF_SERVO; i++)
    {
      set_pos(i, filter_sitting_height_neutral[i] * 800 + filter_leg_opening_neutral[i] * 400 + filter_leg_up_1[i] * 1600);
    }

    delay(500);

    for (unsigned char i = 0; i < NUM_OF_SERVO; i++)
    {
      set_pos(i, filter_sitting_height_neutral[i] * 800 + filter_leg_opening_neutral[i] * 400 + filter_leg_up_2[i] * 1600);
    }
    delay(500);
  }
  */
}