#include "battle_15.h"

MATCH void func_800AE640(void) {
    /* FAKE: Pin the battle work pointer to $a0; clean C left
     * the long-lived pointer in $a1 while $a0 stayed free. */
    FAKE_REG(u8*, work, "a0");
    u8  step;
    u8* tail;
    u32 counter;
    u16 sum;
    u8  count;

    work = TASK_BYTES;
    if (work[0xA] < 8) {
        work[0xA]++;
        work = TASK_BYTES;
    }
    step                 = work[9] + 1;
    counter              = *(u32*)(work + 0x10) + 2;
    sum                  = *(u16*)(work + 0x30) + counter;
    work[9]              = step;
    *(u32*)(work + 0x10) = counter;
    *(u16*)(work + 0x30) = sum;
    if (step == 12) {
        tail                 = TASK_BYTES;
        count                = tail[1];
        *(s32*)(tail + 0x10) = -6;
        tail[1]              = count + 1;
    }
}
