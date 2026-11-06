#include "engine/slus/slus.h"

/* pops the g_AreaCellPrims row id at the free ring index g_AreaCellPrimFreeIndex and advances it, returning
 * 0 when the ring is empty.
 */
MATCH u16 Area_AllocCellPrimRow(void) {
    u16 index;
    u16 row_id;

    index = g_AreaCellPrimFreeIndex;
    if ((index & HALF_MASK) == 0) {
        return 0;
    }
    row_id                  = g_AreaCellPrimFreeIds[index];
    g_AreaCellPrimFreeIndex = (index + 1) & 0x3FF;
    return row_id;
}
