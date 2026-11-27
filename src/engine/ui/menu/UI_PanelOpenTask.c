#include "engine/slus/slus.h"

/* arms the panel task selected by the panel index and reports
 * 0xFF when it is already armed, otherwise the panel index.
 */
MATCH u8 UI_PanelOpenTask(u8 panel_index, u8 panel) {
    u32 index;

    index = panel_index & BYTE_MASK;
    if (g_UiPanelTasks[index].active == 0) {
        g_UiPanelTasks[index].active = 1;
        g_UiPanelTasks[index].panel  = panel;
        g_UiPanelTasks[index].mode   = 0;
        g_UiPanelTasks[index].state  = 0;
        return panel_index;
    }
    return 0xFF;
}
