#include "boss055_16.h"

MATCH void func_800C3284(void) {
    TASK(PartyMember)->header.flags   = g_BattleEffectBattler->header.flags;
    TASK(PartyMember)->unk_48         = g_BattleEffectBattler->unk_48;
    TASK(PartyMember)->scale.x        = g_BattleEffectBattler->scale.x;
    TASK(PartyMember)->scale.y        = g_BattleEffectBattler->scale.y;
    TASK(PartyMember)->unk_27         = g_BattleEffectBattler->unk_27;
    TASK(PartyMember)->unk_28         = g_BattleEffectBattler->unk_28;
    TASK(PartyMember)->unk_2A         = g_BattleEffectBattler->unk_2A;
    TASK(PartyMember)->screen_x.value = g_BattleEffectBattler->screen_x.value;
    TASK(PartyMember)->screen_y.value = g_BattleEffectBattler->screen_y.value;
    TASK(PartyMember)->depth          = g_BattleEffectBattler->depth;
    TASK(PartyMember)->unk_5C         = g_BattleEffectBattler->unk_5C;
    TASK(PartyMember)->unk_5D         = g_BattleEffectBattler->unk_5D;
    TASK(PartyMember)->unk_5E         = g_BattleEffectBattler->unk_5E;
    TASK(PartyMember)->unk_5F         = g_BattleEffectBattler->unk_5F;

    if (TASK(PartyMember)->unk_48 != 0) {
        TASK(PartyMember)->screen_x.value += Area_RoundSpriteCoordinate(D_800C34D4[TASK(PartyMember)->header.mode].vx * TASK(PartyMember)->scale.x, TASK(PartyMember)->scale.x);
        TASK(PartyMember)->screen_y.value += Area_RoundSpriteCoordinate(D_800C34D4[TASK(PartyMember)->header.mode].vy * TASK(PartyMember)->scale.y, TASK(PartyMember)->scale.y);
    } else {
        TASK(PartyMember)->screen_x.value += Area_RoundSpriteCoordinate(TO_COORD(D_800C34D4[TASK(PartyMember)->header.mode].vx), TO_COORD(1));
        TASK(PartyMember)->screen_y.value += Area_RoundSpriteCoordinate(TO_COORD(D_800C34D4[TASK(PartyMember)->header.mode].vy), TO_COORD(1));
    }
}
