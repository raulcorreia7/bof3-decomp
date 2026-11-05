#include "start_08.h"

/* Panel handler table and draw helpers owned by this overlay. */

MATCH void func_801E9DF4(void) {
    D_801ED43C[g_MenuPanelTaskCurrent->state]();
    func_801DCDB8(g_MenuPanelTaskCurrent->x, g_MenuPanelTaskCurrent->y, ((u8*)g_MenuPanelTaskCurrent)[0xA],
                  ((u8*)g_MenuPanelTaskCurrent)[0xC], ((s16*)g_MenuPanelTaskCurrent)[8]);
    if (((u8*)g_MenuPanelTaskCurrent)[0xC] != 0) {
        ((u16*)g_MenuPanelTaskCurrent)[8] = (u16)(((u16*)g_MenuPanelTaskCurrent)[8] + 0x40);
        Menu_DrawCursorFrame((u16)(g_MenuPanelTaskCurrent->x + 4), g_MenuPanelTaskCurrent->y, 0x44, 0x34, 0, 6);
    }
}
