#include "area149_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3460(void) {
    s8* step;
    u16 height;

    step = &g_SceneEventStep;
    switch (*step) {
        case 0:
            if (g_AreaCameraX == 0x77FF) {
                g_AreaCameraX = 0x63FF;
                g_AreaScrollTargetX += TO_COORD(20);
                g_AreaTileOriginX += 20;
                g_PartyX += TO_COORD(20);
                height         = Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY);
                g_ScrollHeight = height;
                Area_AdvanceScroll(height);
                Area_RefreshCellGrid();
                D_80147A8C += TO_COORD(20);
                D_80147A96 = Area_SampleHeight(D_80147A8C, g_AreaFocusY);
            }
            if (TIMER_EXPIRED(LOHU(D_801448EE))) {
                *step = 2;
            }
            break;
        case 2:
            g_ScriptVars[3]  = 0x20;
            g_SceneEventMode = 0;
            *step            = 0;
            Game_RequestAreaChange(AREA_ID_MYRIA_STATION_WORKERS, TO_COORD(40), TO_COORD(99), 0x81);
            break;
        case 10:
            if (g_AreaCameraX == 0x63FF) {
                g_AreaCameraX = 0x77FF;
                g_AreaScrollTargetX -= TO_COORD(20);
                g_AreaTileOriginX -= 20;
                g_PartyX -= TO_COORD(20);
                height         = Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY);
                g_ScrollHeight = height;
                Area_AdvanceScroll(height);
                Area_RefreshCellGrid();
                D_80147A8C -= TO_COORD(20);
                D_80147A96 = Area_SampleHeight(D_80147A8C, g_AreaFocusY);
            }
            if (TIMER_EXPIRED(LOHU(D_801448EE))) {
                *step = 12;
            }
            break;
        case 12:
            g_ScriptVars[3]  = 0x20;
            g_SceneEventMode = 0;
            *step            = 0;
            Game_RequestAreaChange(AREA_ID_CAER_XHAN_LIFT_AREA, TO_COORD(10), TO_COORD(25), 0x81);
            break;
    }
}
#else
INCLUDE_ASM(func_801F3460);
#endif
