#include "battle_03.h"

MATCH void func_801E383C(void) {
    u8 value;

    if (g_BattleSelectionLatch != 0) {
        value = *D_801EB4D8;
        if ((value == g_Task->slot) || (value & BATTLE_TARGET_ENEMY_SIDE)) {
            g_Task->unk_07 = (u8)GFX_AllocPaletteFade((u8*)g_Task, 0, 0, 0, 0);
            g_Task->step   = 1;
        }
    }
}
