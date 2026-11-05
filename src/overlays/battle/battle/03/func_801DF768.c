#include "battle_03.h"

MATCH void func_801DF768(void) {
    if ((g_BattleSelectionLatch != 0u) && ((*D_801EB4D8 == g_Task->slot) || ((*D_801EB4D8 & 0x80u) != 0u))) {
        g_Task->unk_07 = (u8)GFX_AllocPaletteFade((u8*)g_Task, 0, 0, 0, 0);
        g_Task->step   = 1u;
    }
}
