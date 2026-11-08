#include "battle_15.h"

MATCH void func_8009B700(void) {
    volatile u16* scroll_a;
    volatile u16* scroll_b;
    u8            counter;
    s8            delta;
    u32           index;

    if (g_AreaCameraMoving == 0) {
        index            = g_Battle.scroll_dir;
        g_AreaCameraStep = 0x80;
        scroll_a         = &g_AreaTargetCellX;
        *scroll_a -= D_800B44C0[index].x;
        counter           = g_Battle.ui_state;
        delta             = D_800B44C0[index].y;
        g_Battle.ui_state = counter + 2;
        scroll_b          = &g_AreaTargetCellY;
        *scroll_b -= delta;
    }
}
