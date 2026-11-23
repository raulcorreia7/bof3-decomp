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
        party         = &g_PartyPos.x.fixed;
        focus         = &g_PartyActors[0].pos.x.fixed;
        g_AreaTileOriginX += 20;
        *scroll += TO_COORD(20);
        *party += TO_COORD(20);
        height                    = Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY);
        g_PartyPos.z.part.integer = height;
        Area_ScrollAdvance(height);
        Area_CellRefreshGrid();
        *focus += TO_COORD(20);
        g_AreaFocus.z.part.integer = Area_HeightSample(*focus, g_AreaFocus.y.fixed);
    }
}
