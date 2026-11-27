#include "boss018_16.h"

MATCH void func_800C1CD8(void) {
    if (SELF(Actor)->unk_05 == 4) {
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
    D_800C2D60[SELF(Actor)->header.mode]();
}
