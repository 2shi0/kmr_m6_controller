#include "ard_ics.h"

ard_ics::ard_ics(int tx_pin) {
  Serial1.begin(115200, SERIAL_8E1, -1, tx_pin);
  while(!Serial1) delay(1);
}

void ard_ics::set_pos(unsigned char id, int pos) {
  if (pos < 3500 || pos > 11500) return;

  tx[0] = 0x80 | id;
  tx[1] = (unsigned char)(pos >> 7 & 0x7F);
  tx[2] = (unsigned char)(pos & 0x7F);

  for (int i = 0; i < sizeof(tx) / sizeof(tx[0]); i++) {
    Serial1.write(tx[i]);
  }
}
