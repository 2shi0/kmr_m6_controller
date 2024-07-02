#include "task_maker.h"

void task_maker::create_task(char *name, int priority)
{
  xTaskCreate(
      [](void *this_pointer)
      {
        static_cast<task_maker *>(this_pointer)->task();
      },
      name,
      4096,
      this,
      priority,
      NULL);
}

void task_maker::task() {}