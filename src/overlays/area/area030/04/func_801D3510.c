#include "area030_04.h"

/* Ticks down the AREA030 scratch counter at +0x09, advancing the
 * state byte when it reaches zero, then runs the shared state dispatcher. */
MATCH void func_801D3510(void) {
    u8* head = (u8*)g_Task;
    u8* tail;
    u8  value;

    value   = (u8)(head[9] - 1);
    head[9] = value;

    tail = (u8*)g_Task;
    if (tail[9] == 0) {
        tail[1] = (u8)(tail[1] + 1);
    }

    Area_AddActor();
}
