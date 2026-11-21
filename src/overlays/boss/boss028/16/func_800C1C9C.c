#include "boss028_16.h"

#ifdef NON_MATCHING
NON_MATCHING void func_800C1C9C(void) {
    /* FAKE: retail keeps the party in a1 and battler in v1 across the coordinate copies. */
    FAKE_REG(PartyMember*, party, "a1");
    FAKE_REG(PartyMember*, battler, "v1");
    /* FAKE: retail loads the battler's y coordinate into v0 before preparing the call. */
    FAKE_REG(s32, pos_y, "v0");
    u32 slot;

    BOSS028_PARTY->unk_24 = 0;
    BOSS028_PARTY->unk_2A = 0;
    BOSS028_PARTY->unk_48 = 0;
    BOSS028_PARTY->unk_29 = 2;
    Area_SelectSceneRecord(0x15C);
    Script_Select(4);
    party                              = BOSS028_PARTY;
    battler                            = g_BattleEffectBattler;
    COORD_INT(party->pos.x)            = COORD_INT(battler->pos.x) + 7;
    pos_y                              = battler->pos.y.fixed;
    party->pos.y.fixed                 = pos_y;
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
