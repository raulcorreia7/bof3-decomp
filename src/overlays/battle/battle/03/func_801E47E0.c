#include "battle_03.h"

/* Advances local-work fields +0x40/+0x44 by +0x0C and then +0x0C by
 * +0x18 while signed +0x40 is at most 0x13FFF; otherwise sets byte +0x03 to 2.
 */
MATCH void func_801E47E0(void) {
    PartyBattler* work;

    work = g_Task;
    if ((s32)work->scale.x <= 0x13FFF) {
        work->scale.x += work->unk_0C;
        work->scale.y += work->unk_0C;
        work->unk_0C += work->unk_18;
    } else {
        work->unk_03 = 2;
    }
}
