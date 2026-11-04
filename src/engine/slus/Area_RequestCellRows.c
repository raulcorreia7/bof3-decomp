#include "engine/slus/slus.h"

/* queues and clears the low-12-bit prim_id of entry, then queues and
 * clears the nonzero pad1 and pad2 links of its g_AreaCellPrims row.
 */
MATCH void Area_RequestCellRows(AreaCell* entry) {
    u16 id;
    u16 value;

    id = entry->prim_id & 0xFFF;
    if (id != 0) {
        Area_FreeCellPrimRow(id);
        entry->prim_id = 0;
        value          = g_AreaCellPrims[id][1].pad1;
        if (value != 0) {
            Area_FreeCellPrimRow(value);
            g_AreaCellPrims[id][1].pad1 = 0;
        }
        value = g_AreaCellPrims[id][1].pad2;
        if (value != 0) {
            Area_FreeCellPrimRow(value);
            g_AreaCellPrims[id][1].pad2 = 0;
        }
    }
}
