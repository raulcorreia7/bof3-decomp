#include "battle_15.h"

/* func_8009B9A0 */
MATCH void Battle_SucceedEscape(void) {
    s32          count;
    u8           index;
    volatile u8* cell;

    if (g_AreaCameraMoving == 0) {
        count = 0;
        Area_ScrollAdvance(Area_HeightSample(g_AreaScrollTargetCoordX.fixed, g_AreaScrollTargetCoordY.fixed));
        do {
            index = (count & BYTE_MASK);
            GFX_PaletteFreeFadeTarget(&g_BattleEnemyBattlers[index]);
            count++;
        } while ((count & BYTE_MASK) < 8U);
        func_800ACF80();
        func_801D9484();
        func_801DE560(2u, 0u, 0u, 45u, UI_MessageGetText(0x10));
        cell = &g_Battle.ui_mode;
        cell[0] += 1;
    }
}
