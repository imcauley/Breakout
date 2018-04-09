#ifndef BUFFER_H
#define BUFFER_H

#include "types.h"

void start_queue();
void enque(UINT8 code);
UINT8 deque();
bool queue_is_empty();

#endif