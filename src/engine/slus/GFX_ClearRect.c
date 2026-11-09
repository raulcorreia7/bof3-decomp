#include "engine/slus/slus.h"

/* clears one rectangular display region.
 */
MATCH void GFX_ClearRect(s16 x, s16 y, s16 width, s16 height) {
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    ClearImage(&rect, 0, 0, 0);
}
