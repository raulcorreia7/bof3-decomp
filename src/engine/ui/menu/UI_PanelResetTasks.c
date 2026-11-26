#include "engine/slus/slus.h"

/* clears the 22 front-end slots field by field and the trailing flag byte g_UiPanelMode.
 */
MATCH void UI_PanelResetTasks(void) {
    s32 i;

    for (i = 0; i < MENU_PANEL_COUNT; i++) {
        g_UiPanelTasks[i].active        = 0;
        g_UiPanelTasks[i].panel         = 0;
        g_UiPanelTasks[i].mode          = 0;
        g_UiPanelTasks[i].state         = 0;
        g_UiPanelTasks[i].layer         = 0;
        g_UiPanelTasks[i].pos.vx        = 0;
        g_UiPanelTasks[i].pos.vy        = 0;
        g_UiPanelTasks[i].unk_08        = 0;
        g_UiPanelTasks[i].unk_09        = 0;
        g_UiPanelTasks[i].unk_0A        = 0;
        g_UiPanelTasks[i].unk_0B        = 0;
        g_UiPanelTasks[i].unk_0C        = 0;
        g_UiPanelTasks[i].flags         = 0;
        g_UiPanelTasks[i].unk_0E        = 0;
        g_UiPanelTasks[i].u.addr.unk_10 = 0;
        g_UiPanelTasks[i].u.addr.unk_12 = 0;
        g_UiPanelTasks[i].u.addr.unk_14 = 0;
        g_UiPanelTasks[i].u.addr.unk_16 = 0;
        g_UiPanelTasks[i].u.addr.unk_18 = 0;
        g_UiPanelTasks[i].u.addr.unk_1A = 0;
        g_UiPanelTasks[i].u.addr.unk_1C = 0;
        g_UiPanelTasks[i].u.addr.unk_1E = 0;
    }
    g_UiPanelMode = 0;
}
