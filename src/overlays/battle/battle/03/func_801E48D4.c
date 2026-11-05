#include "battle_03.h"

/* advances the active local-work timers by adding +0x10 into +0x44
 * and +0x1C into +0x10, then re-arms the effect when +0x44 went negative.
 */
MATCH void func_801E48D4(void) {
    PartyBattler* work;
    s32           timer;

    work = g_Task;
    work->unk_44 += work->unk_10;
    work->unk_10 += work->unk_1C;
    timer = (s32)work->unk_44;
    if (timer < 0) {
        func_801E54EC();
    }
}
