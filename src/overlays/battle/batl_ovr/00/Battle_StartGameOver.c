#include "batl_ovr_00.h"

/* GFX_CopyPalette(0x1A) copies palette row 26 (0x80036C00), the BATL_OVR bank, into the
 * working palette and marks it for upload. */
/* func_801EEC40 */
MATCH void Battle_StartGameOver(void) {
    u8* counter = &g_Battle.ui_step;

    UI_SetMode(0x13);
    GFX_CopyPalette(26);

    *counter += 1;
}
