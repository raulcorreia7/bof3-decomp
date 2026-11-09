#include "boss023_16.h"
#include "area/spad.h"

MATCH void func_800C1848(void) {
    if (g_Task->unk_05 == 3) {
        g_BattleCurrentEnemy->script = D_800C1A4C;
    } else {
        g_BattleCurrentEnemy->script = D_800C1A40;
    }
    if (g_Task->unk_05 == 3) {
        g_BattleCurrentEnemy->unk_E8 = D_800C1A58;
    } else if (g_Task->unk_05 == 4) {
        g_BattleCurrentEnemy->unk_E8 = D_800C1A60;
    } else {
        g_BattleCurrentEnemy->unk_E8 = D_800C1A68;
    }
    g_BattleCurrentEnemy->unk_E4 = func_800C1934;
    g_Task->header.mode          = 2;
    Actor_StepAnimLoop();
}
