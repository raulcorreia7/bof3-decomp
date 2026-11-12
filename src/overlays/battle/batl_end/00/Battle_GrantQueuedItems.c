#include "batl_end_00.h"

/* func_801EF870 */
MATCH void Battle_GrantQueuedItems(void) {
    u8  slot;
    u16 item;

    if (EMI_IsReady() != 0) {
        for (slot = 0; slot < D_80146327.count; slot++) {
            item = PartyGrantQueue_Item(slot);
            Item_Add(item >> 8, item & BYTE_MASK, D_80146327.levels[slot], 0);
        }

        g_Battle.phase.step     = 4;
        g_Battle.phase.sub_step = 0;
        g_Battle.ui_step        = 0;
        g_Battle.ui_state       = 0;
    }
}
