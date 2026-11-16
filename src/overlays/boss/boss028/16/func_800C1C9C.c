#include "boss028_16.h"

#ifdef NON_MATCHING
NON_MATCHING void func_800C1C9C(void) {
    PartyMember* party;
    PartyMember* battler;
    u32          slot;

    BOSS028_PARTY->unk_24 = 0;
    BOSS028_PARTY->unk_2A = 0;
    BOSS028_PARTY->unk_48 = 0;
    BOSS028_PARTY->unk_29 = 2;
    Area_SelectSceneRecord(0x15C);
    Actor_SelectScript(4);
    party                              = BOSS028_PARTY;
    battler                            = g_BattleEffectBattler;
    COORD_INT(party->pos.x)            = COORD_INT(battler->pos.x) + 7;
    party->pos.y.fixed                 = battler->pos.y.fixed;
    party->unk_20                      = -0x20;
    party->unk_14                      = 0;
    party->unk_09                      = 6;
    COORD_INT(party->pos.z)            = COORD_INT(battler->pos.z) + 0x1000;
    slot                               = Battle_AllocEffect(3, 2) & BYTE_MASK;
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].target.party = BOSS028_PARTY;
    BOSS028_PARTY->header.step += 1;
}
#else
INCLUDE_ASM(func_800C1C9C);
#endif
