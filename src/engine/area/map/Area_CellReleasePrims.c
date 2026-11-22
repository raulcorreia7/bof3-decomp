#include "engine/slus/slus.h"

/* releases the cell's low-12-bit prim_slot, then the nonzero pad1 and pad2 link
 * slots of its g_AreaCellPrims slot.
 */
MATCH void Area_CellReleasePrims(AreaCell* entry) {
    u16 id;
    u16 value;

    id = entry->prim_slot & AREA_CELL_PRIM_MASK;
    if (id != 0) {
        Area_CellFreePrimSlot(id);
        entry->prim_slot = 0;
        value            = g_AreaCellPrims[id][1].pad1;
        if (value != 0) {
            Area_CellFreePrimSlot(value);
            g_AreaCellPrims[id][1].pad1 = 0;
        }
        value = g_AreaCellPrims[id][1].pad2;
        if (value != 0) {
            Area_CellFreePrimSlot(value);
            g_AreaCellPrims[id][1].pad2 = 0;
        }
    }
}
