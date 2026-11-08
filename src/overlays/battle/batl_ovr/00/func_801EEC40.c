#include "batl_ovr_00.h"

MATCH void func_801EEC40(void) {
    u8* counter = &g_Battle.ui_step;

    UI_SetMode(0x13);
    GFX_CopyPalette(0x1A);

    *counter += 1;
}
