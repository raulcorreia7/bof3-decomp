#include "engine/slus/slus.h"

/* clears the 22 front-end slots field by field and the trailing flag byte g_MenuPanelMode.
 */
MATCH void Menu_ResetPanelTasks(void) {
    s32 i;

    for (i = 0; i < 22; i++) {
        g_MenuPanelTasks[i].unk_00[0] = 0;
        g_MenuPanelTasks[i].unk_00[1] = 0;
        g_MenuPanelTasks[i].unk_00[2] = 0;
        g_MenuPanelTasks[i].state     = 0;
        g_MenuPanelTasks[i].unk_0F    = 0;
        g_MenuPanelTasks[i].x         = 0;
        g_MenuPanelTasks[i].y         = 0;
        g_MenuPanelTasks[i].unk_08    = 0;
        g_MenuPanelTasks[i].unk_09    = 0;
        g_MenuPanelTasks[i].unk_0A    = 0;
        g_MenuPanelTasks[i].unk_0B    = 0;
        g_MenuPanelTasks[i].unk_0C    = 0;
        g_MenuPanelTasks[i].flags     = 0;
        g_MenuPanelTasks[i].unk_0E    = 0;
        g_MenuPanelTasks[i].unk_10    = 0;
        g_MenuPanelTasks[i].unk_12    = 0;
        g_MenuPanelTasks[i].unk_14    = 0;
        g_MenuPanelTasks[i].unk_16    = 0;
        g_MenuPanelTasks[i].unk_18    = 0;
        g_MenuPanelTasks[i].unk_1A    = 0;
        g_MenuPanelTasks[i].unk_1C    = 0;
        g_MenuPanelTasks[i].unk_1E    = 0;
    }
    g_MenuPanelMode = 0;
}
