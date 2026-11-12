#include "boss018_16.h"

MATCH void func_800C1DC4(void) {
    if ((SYS_TestFlag(g_SceneFlags, 30) != 0) || (SYS_TestFlag(g_SceneFlags, 35) != 0)) {
        if (((PartyMember*)g_Task)->slot == 4) {
            g_BattleCurrentEnemy->hp = D_801FD702;
        } else {
            g_BattleCurrentEnemy->hp = D_801FD6FC;
        }
    }
    if (((PartyMember*)g_Task)->slot == 5) {
        ((PartyMember*)g_Task)->facing |= 2;
        g_BattleCurrentEnemy->script = D_800C2C74;
    } else {
        g_BattleCurrentEnemy->script = D_800C2C5C;
    }
    g_BattleCurrentEnemy->unk_E4        = func_800C2074;
    g_BattleCurrentEnemy->unk_E8        = &D_800C2CA4;
    ((PartyMember*)g_Task)->header.mode = 2;
    Actor_StepAnimLoop();
}
