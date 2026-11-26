#include "boss028_16.h"

MATCH void func_800C1F2C(void) {
    PartyMember* task;

    task = SELF(PartyMember);
    COORD_INT(task->pos.z) += task->unk_14;
    task->unk_14 += task->unk_20;
    /* FAKE: the s16 return is read as s32; retail adds 0x1000 to the raw register. */
    if (COORD_INT(task->pos.z) > ((s32 (*)(s32, s32))Area_HeightSample)(task->pos.x.fixed, task->pos.y.fixed) + 0x1000) {
        g_BattleEffectBattler->header.mode = 5;
        g_BattleEffectBattler->header.step = 0;
        Effect_Reset();
    }
}
