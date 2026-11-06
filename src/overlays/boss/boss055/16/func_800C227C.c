#include "boss055_16.h"

MATCH void func_800C227C(void) {
    if (g_BattleState & BATTLE_STATE_EFFECT_PLAYING) {
        if (LOHU(g_BattleActionId) == ABILITY_HOLOCAUST) {
            ((PartyBattler*)g_Task)->unk_0B      = 1;
            D_801463BE                           = 8;
            ((PartyBattler*)g_Task)->header.step = 3;
            return;
        }
        func_801E567C();
    }
}
