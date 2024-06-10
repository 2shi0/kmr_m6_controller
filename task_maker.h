#ifndef _TASK_MAKER_h_
#define _TASK_MAKER_h_
#include <Arduino.h>
class task_maker {
public:
  void create_task(char *name);
  virtual void task();

private:
};

#endif