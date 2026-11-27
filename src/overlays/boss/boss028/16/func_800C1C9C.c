#include "boss028_16.h"

/* Moves the boss028 party member beside the effect battler and starts its effect. */
MATCH void func_800C1C9C(void) {
    PartyMember* party;
    PartyMember* battler;
    u32          slot;

    SELF(PartyMember)->unk_24 = 0;
    SELF(PartyMember)->unk_2A = 0;
    SELF(PartyMember)->unk_48 = 0;
    SELF(PartyMember)->unk_29 = 2;
    Area_SceneSelectRecord(0x15C);
    Script_Select(4);
    party                              = SELF(PartyMember);
    battler                            = g_BattleEffectBattler;
    COORD_INT(party->pos.x)            = COORD_INT(battler->pos.x) + 7;
    party->pos.y.fixed                 = battler->pos.y.fixed;
    COORD_INT(party->pos.z)            = COORD_INT(battler->pos.z) + 0x1000;
    party->unk_20                      = -0x20;
    party->unk_14                      = 0;
    party->unk_09                      = 6;
    slot                               = Battle_AllocEffect(3, 2) & BYTE_MASK;
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].target.party = SELF(PartyMember);
    SELF(PartyMember)->header.step += 1;
}
