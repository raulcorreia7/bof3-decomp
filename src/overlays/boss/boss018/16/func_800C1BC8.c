#include "boss018_16.h"

MATCH void func_800C1BC8(void) {
    if (SYS_TestFlag(g_SceneFlags, 55) != 0) {
        g_BattleCurrentEnemy->hp = D_801FD700;
        g_BattleCurrentEnemy->ap = D_801FD6FE;
    } else {
        SYS_SetFlag(g_SceneFlags, 55U);
    }
    g_BattleCurrentEnemy->script        = &D_800C2C50;
    g_BattleCurrentEnemy->unk_E4        = func_800C1C6C;
    g_BattleCurrentEnemy->unk_E8        = &D_800C2C9C;
    ((PartyMember*)g_Task)->header.mode = 2;
    Actor_StepAnimLoop();
}
