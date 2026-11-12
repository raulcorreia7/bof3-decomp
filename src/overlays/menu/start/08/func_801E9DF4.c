#include "start_08.h"

/* Panel handler table and draw helpers owned by this overlay. */

MATCH void func_801E9DF4(void) {
    g_MenuStartPanel11StateFuncs[g_MenuCurrentPanel->state]();
    Menu_DrawFormationPreview(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, g_MenuCurrentPanel->unk_0A, g_MenuCurrentPanel->unk_0C, ((s16*)g_MenuCurrentPanel)[8]);
    if (g_MenuCurrentPanel->unk_0C != 0) {
        g_MenuCurrentPanel->u.addr.unk_10 = (g_MenuCurrentPanel->u.addr.unk_10 + 0x40);
        Menu_DrawCursorFrame((g_MenuCurrentPanel->pos.x + 4), g_MenuCurrentPanel->pos.y, 68, 52, 0, 6);
    }
}
