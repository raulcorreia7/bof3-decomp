#include "boss055_16.h"

MATCH void func_800C227C(void) {
    if (g_Battle.state & BATTLE_STATE_EFFECT_PLAYING) {
        if (LOHU(g_Battle.action_id) == ABILITY_HOLOCAUST) {
            ((PartyMember*)g_Task)->param.unk_0B = 1;
            D_801463BE                           = 8;
            ((PartyMember*)g_Task)->header.step  = 3;
            return;
        }
        func_801E567C();
    }
}
