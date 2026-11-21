#include "start_08.h"

/* Panel handler table and draw helpers owned by this overlay. */

MATCH void func_801E9DF4(void) {
    g_MenuStartPanel11Steps[g_UiPanelCurrent->state]();
    Menu_DrawFormationPreview(g_UiPanelCurrent->pos.x, g_UiPanelCurrent->pos.y, g_UiPanelCurrent->unk_0A, g_UiPanelCurrent->unk_0C, ((s16*)g_UiPanelCurrent)[8]);
    if (g_UiPanelCurrent->unk_0C != 0) {
        g_UiPanelCurrent->u.addr.unk_10 = (g_UiPanelCurrent->u.addr.unk_10 + 0x40);
        Menu_DrawCursorFrame((g_UiPanelCurrent->pos.x + 4), g_UiPanelCurrent->pos.y, 68, 52, 0, 6);
    }
}
