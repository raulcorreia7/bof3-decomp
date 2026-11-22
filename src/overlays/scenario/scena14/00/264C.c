#include "scena14_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F924C(void) {
    s32* scroll;
    s32* party;
    s32* focus;
    u16  height;

    if (g_AreaCameraX == 0x77FF) {
        g_AreaCameraX = 0x63FF;
        scroll        = &g_AreaScrollTargetX;
        party         = &g_PartyX;
        focus         = &D_80147A8C;
        g_AreaTileOriginX += 20;
        *scroll += TO_COORD(20);
        *party += TO_COORD(20);
        height         = Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY);
        g_ScrollHeight = height;
        Area_AdvanceScroll(height);
        Area_RefreshCellGrid();
        *focus += TO_COORD(20);
        D_80147A96 = Area_HeightSample(*focus, g_AreaFocusY);
    }
}
