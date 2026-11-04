#include "engine/slus/slus.h"

/* maps the screen cell (column, row) through the cell lookup and
 * returns the pool record for the current display buffer (g_FrameBufferIndex), or 0
 * when the cell has no live entry.
 */
MATCH POLY_FT4* Area_FindCellQuad(s32 column, s32 row) {
    POLY_FT4* primitive;
    s32       index;

    index = Area_ProbeCellId(column, row);
    if (index == 0) {
        primitive = 0;
    } else {
        primitive = &g_AreaCellPrims[index][g_FrameBufferIndex];
    }
    return primitive;
}
