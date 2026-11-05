#include "start_08.h"

/* Panel handler table and draw helpers owned by this overlay. */

MATCH void func_801E9DF4(void) {
    D_801ED43C[g_MenuCurrentPanel->state]();
    func_801DCDB8(g_MenuCurrentPanel->x, g_MenuCurrentPanel->y, ((u8*)g_MenuCurrentPanel)[0xA],
                  ((u8*)g_MenuCurrentPanel)[0xC], ((s16*)g_MenuCurrentPanel)[8]);
    if (((u8*)g_MenuCurrentPanel)[0xC] != 0) {
        ((u16*)g_MenuCurrentPanel)[8] = (u16)(((u16*)g_MenuCurrentPanel)[8] + 0x40);
        Menu_DrawCursorFrame((u16)(g_MenuCurrentPanel->x + 4), g_MenuCurrentPanel->y, 0x44, 0x34, 0, 6);
    }
}
