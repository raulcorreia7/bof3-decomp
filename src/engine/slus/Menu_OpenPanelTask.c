#include "engine/slus/slus.h"

/* arms the panel task selected by the menu id and reports
 * 0xFF when it is already armed, otherwise the menu id.
 */
MATCH u8 Menu_OpenPanelTask(u8 panel_index, u8 handler_index) {
    u32 index;
    /* FAKE: retail holds the success status in $v0 from the branch target. */
    FAKE_REG(s32, status, "v0");

    index = panel_index & BYTE_MASK;
    if (g_MenuPanelTasks[index].active != 0) {
        return 0xFF;
    }
    status = panel_index;
    /* FAKE: keep the success status live across the slot stores. */
    FAKE_USE(status);
    g_MenuPanelTasks[index].active  = 1;
    g_MenuPanelTasks[index].handler = handler_index;
    g_MenuPanelTasks[index].mode    = 0;
    g_MenuPanelTasks[index].state   = 0;
    return status;
}
