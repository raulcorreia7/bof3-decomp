#include "engine/slus/slus.h"

/* arms the panel task selected by the panel index and reports
 * 0xFF when it is already armed, otherwise the panel index.
 */
MATCH u8 UI_PanelOpenTask(u8 panel_index, u8 panel) {
    u32 index;
    /* FAKE: retail holds the success status in $v0 from the branch target. */
    FAKE_REG(s32, status, "v0");

    index = panel_index & BYTE_MASK;
    if (g_UIPanelTasks[index].active != 0) {
        return 0xFF;
    }
    status = panel_index;
    /* FAKE: keep the success status live across the slot stores. */
    FAKE_USE(status);
    g_UIPanelTasks[index].active = 1;
    g_UIPanelTasks[index].panel  = panel;
    g_UIPanelTasks[index].mode   = 0;
    g_UIPanelTasks[index].state  = 0;
    return status;
}
