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

    work = SELF_BYTES;
    if (((PartyMember*)work)->timer < 8) {
        ((PartyMember*)work)->timer++;
        work = SELF_BYTES;
    }
    step                 = work[9] + 1;
    counter              = *(u32*)(work + 0x10) + 2;
    sum                  = *(u16*)(work + 0x30) + counter;
    work[9]              = step;
    *(u32*)(work + 0x10) = counter;
    *(u16*)(work + 0x30) = sum;
    if (step == 12) {
        tail                              = SELF_BYTES;
        count                             = ((PartyMember*)tail)->header.mode;
        *(s32*)(tail + 0x10)              = -6;
        ((PartyMember*)tail)->header.mode = count + 1;
    }
}
