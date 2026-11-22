#include "engine/slus/slus.h"

/* pops the primitive-ring slot at the free ring index g_AreaCellPrimFreeIndex and advances it,
 * returning 0 when the ring is empty.
 */
MATCH u16 Area_CellAllocPrimSlot(void) {
    u16 index;
    u16 prim_slot;

    index = g_AreaCellPrimFreeIndex;
    if ((index & HALF_MASK) == 0) {
        return 0;
    }
    prim_slot               = g_AreaCellPrimFreeSlots[index];
    g_AreaCellPrimFreeIndex = (index + 1) & 0x3FF;
    return prim_slot;
}
