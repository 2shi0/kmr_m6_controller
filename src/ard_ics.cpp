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
  pos = constrain(pos, 3500, 11500);

  tx[0] = 0x80 | id;
  tx[1] = (unsigned char)(pos >> 7 & 0x7F);
  tx[2] = (unsigned char)(pos & 0x7F);

  for (unsigned char i : tx)
  {
    Serial1.write(i);
  }
  vTaskDelay(500 / portTICK_RATE_MS);
}

void ard_ics::set_motion()
{
  for (int i = 0; i < sizeof(motion_data_home)/sizeof(motion_data_home[0]); i++)
  {
    set_pos(i, motion_data_home[i]);
  }
}