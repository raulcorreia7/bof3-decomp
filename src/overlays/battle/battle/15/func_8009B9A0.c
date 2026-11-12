#include "battle_15.h"

MATCH void func_8009B9A0(void) {
    s32          count;
    u8           index;
    volatile u8* cell;

    if (g_AreaCameraMoving == 0) {
        count = 0;
        Area_AdvanceScroll(Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY));
        do {
            index = (count & BYTE_MASK);
            GFX_FreePaletteFadeTarget(&g_BattleEnemyBattlers[index]);
            count++;
        } while ((count & BYTE_MASK) < 8U);
        func_800ACF80();
        func_801D9484();
        func_801DE560(2u, 0u, 0u, 45u, Message_GetText(0x10));
        cell = &g_Battle.ui_state;
        cell[0] += 1;
    }
}
