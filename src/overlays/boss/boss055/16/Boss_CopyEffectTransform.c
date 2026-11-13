#include "boss055_16.h"

/* func_800C3284 */
MATCH void Boss_CopyEffectTransform(void) {
    g_Task->header.flags = g_BattleEffectBattler->header.flags;
    g_Task->unk_48       = g_BattleEffectBattler->unk_48;
    g_Task->scale.x      = g_BattleEffectBattler->scale.x;
    g_Task->scale.y      = g_BattleEffectBattler->scale.y;
    g_Task->unk_27       = g_BattleEffectBattler->unk_27;
    g_Task->unk_28       = g_BattleEffectBattler->unk_28;
    g_Task->unk_2A       = g_BattleEffectBattler->unk_2A;
    g_Task->unk_2E.half  = g_BattleEffectBattler->unk_2E.half;
    g_Task->unk_30.half  = g_BattleEffectBattler->unk_30.half;
    g_Task->depth        = g_BattleEffectBattler->depth;
    g_Task->unk_5C       = g_BattleEffectBattler->unk_5C;
    g_Task->unk_5D       = g_BattleEffectBattler->unk_5D;
    g_Task->unk_5E       = g_BattleEffectBattler->unk_5E;
    g_Task->unk_5F       = g_BattleEffectBattler->unk_5F;

    if (g_Task->unk_48 != 0) {
        g_Task->unk_2E.half += Area_RoundSpriteCoordinate(D_800C34D4[g_Task->header.mode].x * g_Task->scale.x, g_Task->scale.x);
        g_Task->unk_30.half += Area_RoundSpriteCoordinate(D_800C34D4[g_Task->header.mode].y * g_Task->scale.y, g_Task->scale.y);
    } else {
        g_Task->unk_2E.half += Area_RoundSpriteCoordinate(TO_COORD(D_800C34D4[g_Task->header.mode].x), TO_COORD(1));
        g_Task->unk_30.half += Area_RoundSpriteCoordinate(TO_COORD(D_800C34D4[g_Task->header.mode].y), TO_COORD(1));
    }
}
