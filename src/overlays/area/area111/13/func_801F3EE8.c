#include "area111_13.h"

MATCH void func_801F3EE8(void) {
    s8 step;

    step = g_SceneEventStep_u8[0] - 1;
    switch (step) {
        case 0:
        case 2:
        case 4:
        case 6:
            func_801BE1B0(0);
            D_801448EE       = 10;
            g_SceneEventStep = 10;
            break;
        case 9: {
            u16* timer = &D_801448EE;

            if (TIMER_EXPIRED(*timer)) {
                g_SceneEventMode      = SCENE_EVENT_NONE;
                g_SceneEventStep      = 0;
                g_SceneEventSelection = 0;
                Game_ClearScriptActive();
            }
        } break;
        case 19:
            Area_SetCellPalette(0x11, 0xB7);
            D_801448EE       = 0x1E;
            g_SceneEventStep = 0x15;
            break;
        case 20: {
            u16* timer = &D_801448EE;

            if (TIMER_EXPIRED(*timer)) {
                g_AreaScrollTargetX    = 0x118000;
                g_AreaScrollTargetY    = 0xAF0000;
                g_AreaCameraHeightStep = 0;
                g_SceneEventStep       = 0x16;
                g_AreaCameraStep       = g_RouteSpeedScale[4] * 8;
            }
        } break;
        case 21:
            if (g_AreaCameraMoving == 0) {
                Area_SetCellPalette(0x11, 0xAD);
                func_801A4BC0(0x11, 0xAD, 0xA1);
                func_801A4BC0(0x12, 0xAD, 0xA1);
                func_801A4BC0(0x11, 0xAE, 0xC0);
                func_801A4BC0(0x12, 0xAE, 0xC0);
                SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 5));
                SYS_SetFlag(g_SceneEventFlags, 0x28);
                D_801448EE       = 0x1E;
                g_SceneEventStep = 0x17;
            }
            break;
        case 22: {
            u16* timer = &D_801448EE;

            if (TIMER_EXPIRED(*timer)) {
                g_AreaCameraHeightStep = 0;
                g_SceneEventStep       = 0x18;
                g_AreaScrollTargetX    = g_Game.members[0].pos.x.fixed;
                g_AreaScrollTargetY    = g_Game.members[0].pos.y.fixed;
                g_AreaCameraStep       = g_RouteSpeedScale[4] * 8;
            }
        } break;
        case 23:
            if (g_AreaCameraMoving == 0) {
                D_801448EE       = 1;
                g_SceneEventStep = 10;
            }
            break;
    }
}
