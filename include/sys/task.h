#ifndef SYS_TASK_H
#define SYS_TASK_H

#include "types.h"

/* The first three bytes of every task record (field actors, game slots, battle
 * effects, battlers, bmagic effect work): the live flags and the state machine
 * the dispatcher runs. Each record's bytes 0x03 and up differ in role. */
typedef struct TaskHeader {
    u8 flags;
    u8 mode;
    u8 step;
} TaskHeader;

ASSERT_SIZE(TaskHeader, 0x03);

#endif
