#include "batl_end_00.h"

/* func_801EF870 */
MATCH void Battle_GrantQueuedItems(void) {
    u8  slot;
    u16 item;

    if (EMI_IsReady() != 0) {
        for (slot = 0; slot < g_Battle.outcome.drop_count; slot++) {
            item = g_Battle.outcome.drops.items[slot];
            Item_Add(item >> 8, item & BYTE_MASK, g_Battle.outcome.drops.item_counts[slot], 0);
        }

        g_Battle.phase.step     = 4;
        g_Battle.phase.sub_step = 0;
        g_Battle.ui_step        = 0;
        g_Battle.ui_state       = 0;
    }
}
