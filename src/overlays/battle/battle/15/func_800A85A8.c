#include "battle_15.h"

MATCH void func_800A85A8(void) {
    PartyBattler* work;

    work         = (PartyBattler*)g_Task;
    work->unk_20 = work->pos.z.fixed + 0x04000000;
    Actor_SelectScript((work->facing + 0x38) & BYTE_MASK);
    BATTLE_WORK->unk_0B = 0x10;
    BATTLE_WORK->mode++;
}
