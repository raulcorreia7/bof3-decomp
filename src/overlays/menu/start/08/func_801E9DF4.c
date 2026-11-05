#include "start_08.h"

/* Panel handler table and draw helpers owned by this overlay. */

MATCH void func_801E9DF4(void) {
    D_801ED43C[g_MenuPanelTaskCurrent->state]();
    func_801DCDB8(g_MenuPanelTaskCurrent->x, g_MenuPanelTaskCurrent->y, g_MenuPanelTaskCurrent->unk_0A,
                  g_MenuPanelTaskCurrent->unk_0C, (s16)g_MenuPanelTaskCurrent->unk_10);
    if (g_MenuPanelTaskCurrent->unk_0C != 0) {
        g_MenuPanelTaskCurrent->unk_10 = (u16)(g_MenuPanelTaskCurrent->unk_10 + 0x40);
        Menu_DrawCursorFrame((u16)(g_MenuPanelTaskCurrent->x + 4), g_MenuPanelTaskCurrent->y, 0x44, 0x34, 0, 6);
    }
}
