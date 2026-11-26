#include "boss055_16.h"

MATCH void func_800C3284(void) {
    SELF(PartyMember)->header.flags   = g_BattleEffectBattler->header.flags;
    SELF(PartyMember)->unk_48         = g_BattleEffectBattler->unk_48;
    SELF(PartyMember)->scale.x        = g_BattleEffectBattler->scale.x;
    SELF(PartyMember)->scale.y        = g_BattleEffectBattler->scale.y;
    SELF(PartyMember)->unk_27         = g_BattleEffectBattler->unk_27;
    SELF(PartyMember)->unk_28         = g_BattleEffectBattler->unk_28;
    SELF(PartyMember)->unk_2A         = g_BattleEffectBattler->unk_2A;
    SELF(PartyMember)->screen_x.value = g_BattleEffectBattler->screen_x.value;
    SELF(PartyMember)->screen_y.value = g_BattleEffectBattler->screen_y.value;
    SELF(PartyMember)->depth          = g_BattleEffectBattler->depth;
    SELF(PartyMember)->unk_5C         = g_BattleEffectBattler->unk_5C;
    SELF(PartyMember)->unk_5D         = g_BattleEffectBattler->unk_5D;
    SELF(PartyMember)->unk_5E         = g_BattleEffectBattler->unk_5E;
    SELF(PartyMember)->unk_5F         = g_BattleEffectBattler->unk_5F;

    if (SELF(PartyMember)->unk_48 != 0) {
        SELF(PartyMember)->screen_x.value += Area_RoundSpriteCoordinate(D_800C34D4[SELF(PartyMember)->header.mode].vx * SELF(PartyMember)->scale.x, SELF(PartyMember)->scale.x);
        SELF(PartyMember)->screen_y.value += Area_RoundSpriteCoordinate(D_800C34D4[SELF(PartyMember)->header.mode].vy * SELF(PartyMember)->scale.y, SELF(PartyMember)->scale.y);
    } else {
        SELF(PartyMember)->screen_x.value += Area_RoundSpriteCoordinate(TO_COORD(D_800C34D4[SELF(PartyMember)->header.mode].vx), TO_COORD(1));
        SELF(PartyMember)->screen_y.value += Area_RoundSpriteCoordinate(TO_COORD(D_800C34D4[SELF(PartyMember)->header.mode].vy), TO_COORD(1));
    }
}
