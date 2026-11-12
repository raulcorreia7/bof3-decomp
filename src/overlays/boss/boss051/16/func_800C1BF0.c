#include "boss051_16.h"

MATCH void func_800C1BF0(void) {
    PartyMember* battler;
    s32          value;
    u8           value2;
    u8           value3;

    battler = g_Task;
    g_Task  = g_BattleEffectBattler;
    Actor_StepAnimOnce();
    g_Task = battler;
    value2 = battler->unk_09;
    value  = value2 & BYTE_MASK;
    if (value != 0xFF) {
        if (value == 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_ENEMY, 1));
            g_Task->unk_09 = 0xFF;
        } else {
            battler->unk_09 = value2 - 1;
        }
    }
    value3 = g_Task->timer;
    if (value3 == 0) {
        g_BattleEffectBattler->header.mode = 5;
        g_BattleEffectBattler->header.step = 0;
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Task->header.mode += 1;
        return;
    }
    g_Task->timer = value3 - 1;
}
