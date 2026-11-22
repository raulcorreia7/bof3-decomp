#include "boss023_16.h"

MATCH void func_800C1848(void) {
    if (TASK(Actor)->unk_05 == 3) {
        g_BattleCurrentEnemy->script = D_800C1A4C;
    } else {
        g_BattleCurrentEnemy->script = D_800C1A40;
    }
    if (TASK(Actor)->unk_05 == 3) {
        g_BattleCurrentEnemy->unk_E8 = D_800C1A58;
    } else if (TASK(Actor)->unk_05 == 4) {
        g_BattleCurrentEnemy->unk_E8 = D_800C1A60;
    } else {
        g_BattleCurrentEnemy->unk_E8 = D_800C1A68;
    }
    g_BattleCurrentEnemy->unk_E4 = func_800C1934;
    TASK(Actor)->header.mode     = 2;
    Script_AnimStepLoop();
}
