#include "boss051_16.h"

MATCH void func_800C1BF0(void) {
    PartyMember* battler;
    s32          value;
    u8           value2;
    u8           value3;

    battler = SELF(PartyMember);
    g_Self  = g_BattleEffectBattler;
    Script_AnimStepOnce();
    g_Self = battler;
    value2 = battler->unk_09;
    value  = value2 & BYTE_MASK;
    if (value != 0xFF) {
        if (value == 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_ENEMY, 1));
            SELF(PartyMember)->unk_09 = 0xFF;
        } else {
            battler->unk_09 = value2 - 1;
        }
    }
    value3 = SELF(PartyMember)->timer;
    if (value3 == 0) {
        g_BattleEffectBattler->header.mode = 5;
        g_BattleEffectBattler->header.step = 0;
        Battle_MarkDamaged(g_Battle.target_selector);
        SELF(PartyMember)->header.mode += 1;
        return;
    }
    SELF(PartyMember)->timer = value3 - 1;
}
