#include "start_08.h"

/* Panel handler table and draw helpers owned by this overlay. */

MATCH void func_801E9DF4(void) {
    D_801ED43C[g_MenuCurrentPanel->state]();
    func_801DCDB8(g_MenuCurrentPanel->x, g_MenuCurrentPanel->y, g_MenuCurrentPanel->unk_0A, g_MenuCurrentPanel->unk_0C,
                  ((s16*)g_MenuCurrentPanel)[8]);
    if (g_MenuCurrentPanel->unk_0C != 0) {
        g_MenuCurrentPanel->unk_10 = (u16)(g_MenuCurrentPanel->unk_10 + 0x40);
        Menu_DrawCursorFrame((u16)(g_MenuCurrentPanel->x + 4), g_MenuCurrentPanel->y, 0x44, 0x34, 0, 6);
    }
}
