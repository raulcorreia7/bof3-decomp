#include "engine/slus/slus.h"

/* arms the 0x24-stride record selected by the menu id and reports
 * 0xFF when it is already armed, otherwise the menu id.
 */
MATCH s32 Menu_ArmPanelTask(u8 menu_id, u8 handler) {
    u32 offset;
    /* FAKE: retail holds the success status in $v0 from the branch target. */
    MATCH_REG(s32, status, "v0");

    offset = (menu_id & BYTE_MASK) * sizeof(MenuPanelTask);
    if (((u8*)g_MenuPanelTasks)[offset] != 0) {
        return 0xFF;
    }
    status = menu_id;
    /* FAKE: keep the success status live across the slot stores. */
    MATCH_FAKE_USE(status);
    ((u8*)g_MenuPanelTasks)[offset] = 1;
    D_80148331[offset]              = handler; /* record +0x01: the handler to run */
    D_80148332[offset]              = 0;
    D_80148333[offset]              = 0;
    return status;
}
