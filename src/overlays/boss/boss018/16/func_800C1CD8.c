#include "boss018_16.h"
#include "area/spad.h"

MATCH void func_800C1CD8(void) {
    if (g_Task->unk_05 == 4) {
        if (SYS_TestFlag(g_SceneFlags, 52)) {
            g_BattleCurrentEnemy->script = D_800C2C68;
        } else {
            g_BattleCurrentEnemy->script = D_800C2C5C;
        }
    } else {
        if (SYS_TestFlag(g_SceneFlags, 51)) {
            g_BattleCurrentEnemy->script = D_800C2C80;
        } else {
            g_BattleCurrentEnemy->script = D_800C2C74;
        }
    }
    D_800C2D60[g_Task->header.mode]();
}
