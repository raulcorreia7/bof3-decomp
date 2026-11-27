#include "engine/slus/slus.h"

/* clears the 22 front-end slots field by field and the trailing flag byte g_UIPanelMode.
 */
MATCH void UI_PanelResetTasks(void) {
    s32 i;

    for (i = 0; i < MENU_PANEL_COUNT; i++) {
        g_UIPanelTasks[i].active        = 0;
        g_UIPanelTasks[i].panel         = 0;
        g_UIPanelTasks[i].mode          = 0;
        g_UIPanelTasks[i].state         = 0;
        g_UIPanelTasks[i].layer         = 0;
        g_UIPanelTasks[i].pos.vx        = 0;
        g_UIPanelTasks[i].pos.vy        = 0;
        g_UIPanelTasks[i].unk_08        = 0;
        g_UIPanelTasks[i].unk_09        = 0;
        g_UIPanelTasks[i].unk_0A        = 0;
        g_UIPanelTasks[i].unk_0B        = 0;
        g_UIPanelTasks[i].unk_0C        = 0;
        g_UIPanelTasks[i].flags         = 0;
        g_UIPanelTasks[i].unk_0E        = 0;
        g_UIPanelTasks[i].u.addr.unk_10 = 0;
        g_UIPanelTasks[i].u.addr.unk_12 = 0;
        g_UIPanelTasks[i].u.addr.unk_14 = 0;
        g_UIPanelTasks[i].u.addr.unk_16 = 0;
        g_UIPanelTasks[i].u.addr.unk_18 = 0;
        g_UIPanelTasks[i].u.addr.unk_1A = 0;
        g_UIPanelTasks[i].u.addr.unk_1C = 0;
        g_UIPanelTasks[i].u.addr.unk_1E = 0;
    }
    g_UIPanelMode = 0;
}
