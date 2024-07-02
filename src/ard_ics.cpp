#include "ard_ics.h"

ard_ics::ard_ics(uint8_t tx_pin, unsigned char speed)
{
  Serial1.begin(115200, SERIAL_8E1, -1, tx_pin);
  while (!Serial1)
    delay(1);

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
}

void ard_ics::set_pos(unsigned char id, int pos)
{
  id = constrain(id, 0, 31);
  // 135度=4000 45度=1333
  pos = constrain(pos + 7500, 3500, 11500);

  tx[0] = 0x80 | id;
  tx[1] = (unsigned char)(pos >> 7 & 0x7F);
  tx[2] = (unsigned char)(pos & 0x7F);

  for (unsigned char i : tx)
  {
    Serial1.write(i);
  }
}

void ard_ics::set_all(int *pos)
{
  for (unsigned char i = 0; i < NUM_OF_SERVO; i++)
  {
    set_pos(i, pos[i]);
    vTaskDelay(1 / portTICK_RATE_MS);
  }
}

void ard_ics::task()
{

  int motion[4][12];
  for (int i = 0; i < 12; i++)
  {
    motion[0][i] = leg_fw_1[i] - leg_fw_2[i] + leg_up_2[i];
    motion[1][i] = -leg_fw_1[i] + leg_fw_2[i] + leg_up_2[i];
    motion[2][i] = -leg_fw_1[i] + leg_fw_2[i] + leg_up_1[i];
    motion[3][i] = leg_fw_1[i] - leg_fw_2[i] + leg_up_1[i];
  }

  while (1)
  {
    /*
    if (latest_rx == 'n')
      motion_neutral();
    else if (latest_rx == 'f')
      motion_forward();
    else if (latest_rx == 'b')
      motion_back();
    else if (latest_rx == 'r')
      motion_turn_right();
    else if (latest_rx == 'l')
      motion_turn_left();
      bg
    Serial.println(latest_rx);
    */

    for (auto &l : motion)
    {
      vTaskDelay(1000 / portTICK_RATE_MS);
      set_all(l);
    }
  }
}
