#include "engine/slus/slus.h"

/* clears the 22 front-end slots field by field and the trailing flag byte g_MenuPanelMode.
 */
MATCH void Menu_ResetPanelTasks(void) {
    s32 i;

    for (i = 0; i < MENU_PANEL_COUNT; i++) {
        g_MenuPanelTasks[i].active        = 0;
        g_MenuPanelTasks[i].handler       = 0;
        g_MenuPanelTasks[i].mode          = 0;
        g_MenuPanelTasks[i].state         = 0;
        g_MenuPanelTasks[i].layer         = 0;
        g_MenuPanelTasks[i].pos.x         = 0;
        g_MenuPanelTasks[i].pos.y         = 0;
        g_MenuPanelTasks[i].unk_08        = 0;
        g_MenuPanelTasks[i].unk_09        = 0;
        g_MenuPanelTasks[i].unk_0A        = 0;
        g_MenuPanelTasks[i].unk_0B        = 0;
        g_MenuPanelTasks[i].unk_0C        = 0;
        g_MenuPanelTasks[i].flags         = 0;
        g_MenuPanelTasks[i].unk_0E        = 0;
        g_MenuPanelTasks[i].u.addr.unk_10 = 0;
        g_MenuPanelTasks[i].u.addr.unk_12 = 0;
        g_MenuPanelTasks[i].u.addr.unk_14 = 0;
        g_MenuPanelTasks[i].u.addr.unk_16 = 0;
        g_MenuPanelTasks[i].u.addr.unk_18 = 0;
        g_MenuPanelTasks[i].u.addr.unk_1A = 0;
        g_MenuPanelTasks[i].u.addr.unk_1C = 0;
        g_MenuPanelTasks[i].u.addr.unk_1E = 0;
    }
    g_MenuPanelMode = 0;
}
