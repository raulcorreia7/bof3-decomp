#include "start_08.h"

/* Panel handler table selected by the shared panel task's state byte; draw
 * helper owned by this overlay. */

MATCH void func_801EA0B0(void) {
    D_801ED45C[g_MenuCurrentPanel->state]();
    /* clang-format off */
    Menu_DrawCommandRow((s16)g_MenuCurrentPanel->x, (s16)g_MenuCurrentPanel->y,
                        ((u8*)g_MenuCurrentPanel)[0xA], ((u8*)g_MenuCurrentPanel)[0xB], 0);
    /* clang-format on */
}
