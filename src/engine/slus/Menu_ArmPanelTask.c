#include "engine/slus/slus.h"

/* arms the panel task selected by the menu id and reports
 * 0xFF when it is already armed, otherwise the menu id.
 */
MATCH s32 Menu_ArmPanelTask(u8 menu_id, u8 handler) {
    u32 index;
    /* FAKE: retail holds the success status in $v0 from the branch target. */
    MATCH_REG(s32, status, "v0");

    index = menu_id & BYTE_MASK;
    if (g_MenuPanelTasks[index].active != 0) {
        return 0xFF;
    }
    status = menu_id;
    /* FAKE: keep the success status live across the slot stores. */
    MATCH_FAKE_USE(status);
    g_MenuPanelTasks[index].active  = 1;
    g_MenuPanelTasks[index].handler = handler;
    g_MenuPanelTasks[index].mode    = 0;
    g_MenuPanelTasks[index].state   = 0;
    return status;
}
