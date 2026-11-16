#include "area186_13.h"

MATCH void func_801F2C04(void) {
    u16 count;
    s8* step = &g_SceneEventState.step;

    switch (*step) {
        case 0:
            if (g_AreaCameraY == 0x4400) {
                s32* target = &g_AreaScrollTargetY;
                s32* focus  = &g_AreaFocusY;
                s32* party  = &g_PartyY;

                g_AreaCameraY = 0x6200;
                g_AreaTileOriginY -= 0x1E;
                *target -= 0x1E0000;
                *focus -= 0x1E0000;
                *party -= 0x1E0000;
                Area_RefreshCellGrid();
            }
            count = D_801448EE;
            count--;
            D_801448EE = count;
            if (count == 0) {
                D_80146867 = 0x1C;
                D_801448EE = 0xF;
                *step      = 1;
            }
            break;
        case 1:
            count = D_801448EE;
            count--;
            D_801448EE = count;
            if (count == 0) {
                Game_RequestAreaChange(0xAD, 0x120000, 0x460000, 0x81);
                g_SceneEventState.mode = 0;
                *step                  = 0;
            }
            break;
        case 10:
            if (g_AreaCameraY == 0x6C00) {
                s32* target = &g_AreaScrollTargetY;
                s32* focus  = &g_AreaFocusY;
                s32* party  = &g_PartyY;

                g_AreaCameraY = 0x4E00;
                g_AreaTileOriginY += 0x1E;
                *target += 0x1E0000;
                *focus += 0x1E0000;
                *party += 0x1E0000;
                Area_RefreshCellGrid();
            }
            count = D_801448EE;
            count--;
            D_801448EE = count;
            if (count == 0) {
                D_80146867 = 0x1C;
                D_801448EE = 0xF;
                *step      = 11;
            }
            break;
        case 11:
            count = D_801448EE;
            count--;
            D_801448EE = count;
            if (count == 0) {
                Game_RequestAreaChange(0xAD, 0x310000, 0x600000, 0x82);
                g_SceneEventState.mode = 0;
                *step                  = 0;
            }
            break;
    }
}
