#include "start_08.h"

/* Panel handler table selected by the shared panel task's state byte; draw
 * helper owned by this overlay. */

MATCH void func_801EA0B0(void) {
    D_801ED45C[g_MenuCurrentPanel->state]();
    /* clang-format off */
    Menu_DrawCommandRow(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y,
                        g_MenuCurrentPanel->unk_0A, g_MenuCurrentPanel->unk_0B, 0);
    /* clang-format on */
}
