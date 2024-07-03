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

  int motion_fw[4][12];
  for (int i = 0; i < 12; i++)
  {
    motion_fw[0][i] = leg_fw_1[i] - leg_fw_2[i] + leg_up_2[i];
    motion_fw[1][i] = -leg_fw_1[i] + leg_fw_2[i] + leg_up_2[i];
    motion_fw[2][i] = -leg_fw_1[i] + leg_fw_2[i] + leg_up_1[i];
    motion_fw[3][i] = leg_fw_1[i] - leg_fw_2[i] + leg_up_1[i];
  }

  int motion_bk[4][12];
  for (int i = 0; i < 12; i++)
  {
    motion_bk[0][i] = -leg_fw_1[i] + leg_fw_2[i] + leg_up_2[i];
    motion_bk[1][i] = leg_fw_1[i] - leg_fw_2[i] + leg_up_2[i];
    motion_bk[2][i] = leg_fw_1[i] - leg_fw_2[i] + leg_up_1[i];
    motion_bk[3][i] = -leg_fw_1[i] + leg_fw_2[i] + leg_up_1[i];
  }

  int motion_rt[4][12];
  for (int i = 0; i < 12; i++)
  {
    motion_rt[0][i] = -leg_rt_1[i] - leg_rt_2[i] + leg_up_2[i];
    motion_rt[1][i] = leg_rt_1[i] + leg_rt_2[i] + leg_up_2[i];
    motion_rt[2][i] = leg_rt_1[i] + leg_rt_2[i] + leg_up_1[i];
    motion_rt[3][i] = -leg_rt_1[i] - leg_rt_2[i] + leg_up_1[i];
  }

  int motion_lt[4][12];
  for (int i = 0; i < 12; i++)
  {
    motion_lt[0][i] = leg_rt_1[i] + leg_rt_2[i] + leg_up_2[i];
    motion_lt[1][i] = -leg_rt_1[i] - leg_rt_2[i] + leg_up_2[i];
    motion_lt[2][i] = -leg_rt_1[i] - leg_rt_2[i] + leg_up_1[i];
    motion_lt[3][i] = leg_rt_1[i] + leg_rt_2[i] + leg_up_1[i];
  }

  while (1)
  {
    vTaskDelay(1 / portTICK_RATE_MS);
    // nutral
    if (latest_rx == 'n')
    {
      set_all(leg_home);
      continue;
    }

    // forward
    if (latest_rx == 'f')
    {
      for (auto &l : motion_fw)
      {
        vTaskDelay(motion_delay / portTICK_RATE_MS);
        set_all(l);
        if (latest_rx != 'f')
          continue;
      }
    }

    // back
    if (latest_rx == 'b')
    {
      for (auto &l : motion_bk)
      {
        vTaskDelay(motion_delay / portTICK_RATE_MS);
        set_all(l);
        if (latest_rx != 'b')
          continue;
      }
    }

    // right turn
    if (latest_rx == 'r')
    {
      for (auto &l : motion_rt)
      {
        vTaskDelay(motion_delay / portTICK_RATE_MS);
        set_all(l);
        if (latest_rx != 'r')
          continue;
      }
    }

    // left turn
    if (latest_rx == 'l')
    {
      for (auto &l : motion_lt)
      {
        vTaskDelay(motion_delay / portTICK_RATE_MS);
        set_all(l);
        if (latest_rx != 'l')
          continue;
      }
    }
  }
}
