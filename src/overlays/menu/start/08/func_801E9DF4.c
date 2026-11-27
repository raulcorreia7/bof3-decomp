#include "start_08.h"

/* Panel handler table and draw helpers owned by this overlay. */

MATCH void func_801E9DF4(void) {
    g_MenuStartPanel11Steps[g_UIPanelCurrent->state]();
    Menu_DrawFormationPreview(g_UIPanelCurrent->pos.vx, g_UIPanelCurrent->pos.vy, g_UIPanelCurrent->unk_0A, g_UIPanelCurrent->unk_0C, ((s16*)g_UIPanelCurrent)[8]);
    if (g_UIPanelCurrent->unk_0C != 0) {
        g_UIPanelCurrent->u.addr.unk_10 = (g_UIPanelCurrent->u.addr.unk_10 + 0x40);
        Menu_DrawCursorFrame((g_UIPanelCurrent->pos.vx + 4), g_UIPanelCurrent->pos.vy, 68, 52, 0, 6);
    }
}
