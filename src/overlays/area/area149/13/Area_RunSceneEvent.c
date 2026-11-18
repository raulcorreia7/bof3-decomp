#include "area149_13.h"

/* func_801F3460 */
#ifdef NON_MATCHING
NON_MATCHING void Area_RunSceneEvent(void) {
    s8* step;
    u16 height;

    step = &g_SceneEventStep;
    switch (*step) {
        case 0:
            if (g_AreaCameraX == 0x77FF) {
                s32* scroll;
                s32* party;
                s32* focus;

                g_AreaCameraX = 0x63FF;
                scroll        = &g_AreaScrollTargetX;
                party         = &g_PartyX;
                *scroll += TO_COORD(20);
                g_AreaTileOriginX += 20;
                *party += TO_COORD(20);
                height         = Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY);
                g_ScrollHeight = height;
                Area_AdvanceScroll(height);
                Area_RefreshCellGrid();
                focus = &D_80147A8C;
                *focus += TO_COORD(20);
                D_80147A96 = Area_SampleHeight(*focus, g_AreaFocusY);
            }
            if (TIMER_EXPIRED(D_801448EE_U16)) {
                *step = 2;
            }
            break;
        case 2:
            g_ScriptVars[3]  = 0x20;
            g_SceneEventMode = 0;
            *step            = 0;
            Game_RequestAreaChange(AREA_ID_MYRIA_STATION_WORKERS, TO_COORD(40), TO_COORD(99), AREA_ENTRY_MAP_LOADING | FACING_UP);
            break;
        case 10:
            if (g_AreaCameraX == 0x63FF) {
                s32* scroll;
                s32* party;
                s32* focus;

                g_AreaCameraX = 0x77FF;
                scroll        = &g_AreaScrollTargetX;
                party         = &g_PartyX;
                *scroll -= TO_COORD(20);
                g_AreaTileOriginX -= 20;
                *party -= TO_COORD(20);
                height         = Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY);
                g_ScrollHeight = height;
                Area_AdvanceScroll(height);
                Area_RefreshCellGrid();
                focus = &D_80147A8C;
                *focus -= TO_COORD(20);
                D_80147A96 = Area_SampleHeight(*focus, g_AreaFocusY);
            }
            if (TIMER_EXPIRED(D_801448EE_U16)) {
                *step = 12;
            }
            break;
        case 12:
            g_ScriptVars[3]  = 0x20;
            g_SceneEventMode = 0;
            *step            = 0;
            Game_RequestAreaChange(AREA_ID_CAER_XHAN_LIFT_AREA, TO_COORD(10), TO_COORD(25), AREA_ENTRY_MAP_LOADING | FACING_UP);
            break;
    }
}
#else
INCLUDE_ASM(Area_RunSceneEvent);
#endif
