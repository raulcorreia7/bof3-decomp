#ifndef SYS_TASK_H
#define SYS_TASK_H

#include "types.h"

/* The first three bytes of every task record (field actors, game slots, battle effects, battlers, bmagic effect work). */
typedef struct TaskHeader {
    u8 flags;
    u8 mode;
    u8 step;
} TaskHeader;

ASSERT_SIZE(TaskHeader, 0x03);

#endif
