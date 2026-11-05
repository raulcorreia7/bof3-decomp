#include "start_08.h"

/* Panel handler table selected by the shared panel task's state byte; draw
 * helper owned by this overlay. */

MATCH void func_801EA0B0(void) {
    D_801ED45C[g_MenuPanelTaskCurrent->state]();
    Menu_DrawCommandRow((s16)g_MenuPanelTaskCurrent->x, (s16)g_MenuPanelTaskCurrent->y, g_MenuPanelTaskCurrent->unk_0A,
                        g_MenuPanelTaskCurrent->unk_0B, 0);
}
