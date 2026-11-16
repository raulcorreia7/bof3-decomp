#include "area186_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2C04(void) {
    s8* state;

    state = &g_SceneEventStep;
    switch (*state) {
        case 0:
            if (g_AreaCameraY == 0x4400) {
                g_AreaCameraY = 0x6200;
                g_AreaTileOriginY -= 0x1E;
                g_AreaScrollTargetY += TO_COORD(-30);
                g_AreaFocusY += TO_COORD(-30);
                g_PartyY += TO_COORD(-30);
                Area_RefreshCellGrid();
            }
            if (--D_801448EE == 0) {
                D_80146867 = 0x1C;
                D_801448EE = 0x0F;
                *state     = 1;
            }
            break;

        case 1:
            if (--D_801448EE == 0) {
                func_8019FA28(0xAD, TO_COORD(0x12), TO_COORD(0x46), 0x81);
                g_SceneEventMode = 0;
                *state           = 0;
            }
            break;

        case 10:
            if (g_AreaCameraY == 0x6C00) {
                g_AreaCameraY = 0x4E00;
                g_AreaTileOriginY += 0x1E;
                g_AreaScrollTargetY += TO_COORD(30);
                g_AreaFocusY += TO_COORD(30);
                g_PartyY += TO_COORD(30);
                Area_RefreshCellGrid();
            }
            if (--D_801448EE == 0) {
                D_80146867 = 0x1C;
                D_801448EE = 0x0F;
                *state     = 11;
            }
            break;

        case 11:
            if (--D_801448EE == 0) {
                func_8019FA28(0xAD, TO_COORD(0x31), TO_COORD(0x60), 0x82);
                g_SceneEventMode = 0;
                *state           = 0;
            }
            break;
    }
}
#else
INCLUDE_ASM(func_801F2C04);
#endif
