#include "engine/slus/slus.h"

/* pushes the g_AreaCellPrims row id back onto the free ring at index (g_AreaCellPrimFreeIndex - 1) & 0x3FF.
 */
MATCH void Area_FreeCellPrimRow(u16 row_id) {
    u16 index;

    index                        = (g_AreaCellPrimFreeIndex - 1) & 0x3FF;
    g_AreaCellPrimFreeIndex      = index;
    g_AreaCellPrimFreeIds[index] = row_id;
}
