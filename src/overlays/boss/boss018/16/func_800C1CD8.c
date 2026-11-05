#include "boss018_16.h"

MATCH void func_800C1CD8(void) {
    if (TASK_BYTES[5] == 4) {
        if (SYS_TestFlag(g_SceneFlags, 0x34)) {
            g_BattleCurrentEnemy->script = D_800C2C68;
        } else {
            g_BattleCurrentEnemy->script = D_800C2C5C;
        }
    } else {
        if (SYS_TestFlag(g_SceneFlags, 0x33)) {
            g_BattleCurrentEnemy->script = D_800C2C80;
        } else {
            g_BattleCurrentEnemy->script = D_800C2C74;
        }
    }
    D_800C2D60[TASK_BYTES[1]]();
}
