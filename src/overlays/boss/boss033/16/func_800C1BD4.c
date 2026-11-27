#include "boss033_16.h"

MATCH void func_800C1BD4(void) {
    u8* record;
    u8* flags;
    s32 index;

    Script_AnimStepOnce();
    index  = (u8)func_800AC7D0(0);
    record = &g_Actors[index].interaction_flags;
    if (!Actor_Run(record, 0, -0xE, 0x40, -0x400, 0xFF, 0)) {
        Battle_ClearSlotPending(SELF(Actor)->unk_05);
        flags = &g_Battle.outcome.result;
        *flags |= BATTLE_RESULT_VICTORY;
        g_Battle.outcome.reward_exp += g_BattleCurrentEnemy->exp;
        func_800ACFF4();
    }
}
