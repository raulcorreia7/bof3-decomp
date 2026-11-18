#include "battle_15.h"

/* func_8009B794 */
MATCH void Battle_ScrollEscapeBack(void) {
    volatile u16* scroll_a;
    volatile u16* scroll_b;
    u8            counter;
    s8            delta;
    u32           index;

    if (g_AreaCameraMoving == 0) {
        index            = g_Battle.scroll_dir;
        g_AreaCameraStep = 0x40;
        scroll_a         = &g_AreaTargetCellX;
        *scroll_a += g_BattleScrollDeltas[index].dx;
        counter          = g_Battle.ui_mode;
        delta            = g_BattleScrollDeltas[index].dy;
        g_Battle.ui_mode = counter + 1;
        scroll_b         = &g_AreaTargetCellY;
        *scroll_b += delta;
    }
}
