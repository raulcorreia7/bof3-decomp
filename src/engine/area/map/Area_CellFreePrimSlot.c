#include "engine/slus/slus.h"

/* pushes a primitive-ring slot back onto the free ring at index (g_AreaCellPrimFreeIndex - 1) & 0x3FF.
 */
MATCH void Area_CellFreePrimSlot(u16 prim_slot) {
    u16 index;

    index                          = (g_AreaCellPrimFreeIndex - 1) & 0x3FF;
    g_AreaCellPrimFreeIndex        = index;
    g_AreaCellPrimFreeSlots[index] = prim_slot;
}
