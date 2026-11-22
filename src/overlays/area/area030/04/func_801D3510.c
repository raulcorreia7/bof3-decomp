#include "area030_04.h"

/* Ticks down the AREA030 scratch counter at +0x09, advancing the
 * state byte when it reaches zero, then runs the shared state dispatcher. */
MATCH void func_801D3510(void) {
    u8* head = TASK(u8);
    u8* tail;
    u8  value;

    value   = (head[9] - 1);
    head[9] = value;

    tail = TASK(u8);
    if (tail[9] == 0) {
        tail[1] = (tail[1] + 1);
    }

    Area_AddActor();
}
