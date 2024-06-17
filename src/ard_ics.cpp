#include "ard_ics.h"

ard_ics::ard_ics(uint8_t tx_pin)
{
  for (int i = 0; i < NUM_OF_SERVO; i++)
  {
    neutral[i] = filter_sitting_height_neutral[i] * 800 + filter_leg_opening_neutral[i] * 800;
  }
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
}

void ard_ics::task()
{
  while (1)
  {
   if(latest_rx=='n')motion_neutral();
   else
   if(latest_rx=='f')motion_forward();
   else
   if(latest_rx=='b')motion_back();

  Serial.println(latest_rx);
  }
}

void ard_ics::motion_neutral()
{
  for (unsigned char i = 0; i < NUM_OF_SERVO; i++)
  {
    set_pos(i, -filter_sitting_height_neutral[i] * 800 + filter_leg_opening_neutral[i] * 400);
  }
  vTaskDelay(d / portTICK_RATE_MS);
}

void ard_ics::motion_back()
{
  for (unsigned char i = 0; i < NUM_OF_SERVO; i++)
  {
    set_pos(i, neutral[i] + filter_leg_forward_1[i] * 400 + filter_leg_forward_2[i] * -400 + filter_leg_up_1[i] * 800);
  }
  vTaskDelay(d / portTICK_RATE_MS);
  if (latest_rx != 'b')
    return;

  for (unsigned char i = 0; i < NUM_OF_SERVO; i++)
  {
    set_pos(i, neutral[i] + filter_leg_forward_1[i] * -400 + filter_leg_forward_2[i] * 400 + filter_leg_up_1[i] * 800);
  }
  vTaskDelay(d / portTICK_RATE_MS);
  if (latest_rx != 'b')
    return;

  for (unsigned char i = 0; i < NUM_OF_SERVO; i++)
  {
    set_pos(i, neutral[i] + filter_leg_forward_1[i] * -400 + filter_leg_forward_2[i] * 400 + filter_leg_up_2[i] * 800);
  }
  vTaskDelay(d / portTICK_RATE_MS);
  if (latest_rx != 'b')
    return;

  for (unsigned char i = 0; i < NUM_OF_SERVO; i++)
  {
    set_pos(i, neutral[i] + filter_leg_forward_1[i] * 400 + filter_leg_forward_2[i] * -400 + filter_leg_up_2[i] * 800);
  }
  vTaskDelay(d / portTICK_RATE_MS);
}

void ard_ics::motion_forward()
{
  for (unsigned char i = 0; i < NUM_OF_SERVO; i++)
  {
    set_pos(i, neutral[i] + filter_leg_forward_1[i] * -400 + filter_leg_forward_2[i] * 400 + filter_leg_up_1[i] * 800);
  }
  vTaskDelay(d / portTICK_RATE_MS);
  if (latest_rx != 'f')
    return;

  for (unsigned char i = 0; i < NUM_OF_SERVO; i++)
  {
    set_pos(i, neutral[i] + filter_leg_forward_1[i] * 400 + filter_leg_forward_2[i] * -400 + filter_leg_up_1[i] * 800);
  }
  vTaskDelay(d / portTICK_RATE_MS);
  if (latest_rx != 'f')
    return;

  for (unsigned char i = 0; i < NUM_OF_SERVO; i++)
  {
    set_pos(i, neutral[i] + filter_leg_forward_1[i] * 400 + filter_leg_forward_2[i] * -400 + filter_leg_up_2[i] * 800);
  }
  vTaskDelay(d / portTICK_RATE_MS);
  if (latest_rx != 'f')
    return;

  for (unsigned char i = 0; i < NUM_OF_SERVO; i++)
  {
    set_pos(i, neutral[i] + filter_leg_forward_1[i] * -400 + filter_leg_forward_2[i] * 400 + filter_leg_up_2[i] * 800);
  }
  vTaskDelay(d / portTICK_RATE_MS);
}