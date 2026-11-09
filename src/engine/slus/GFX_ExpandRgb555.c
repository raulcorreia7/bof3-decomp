#include "engine/slus/slus.h"

/* expands packed RGB555 pixel pairs into RGB24 bytes, then uploads
 * the result and advances the shared image cursor past the aligned block.
 */
MATCH void GFX_ExpandRgb555(u32* pixels, RECT rect) {
    u8* dst;
    u32 color;
    s32 count;
    s32 remaining;

    count     = rect.w * rect.h * 2;
    dst       = (u8*)D_801459FC;
    remaining = count;
    while (remaining > 0) {
        color  = *pixels++;
        dst[0] = color & 0x1F;
        color >>= 5;
        dst[1] = color & 0x1F;
        color >>= 5;
        dst[2] = color & 0x1F;
        color >>= 6;
        dst[3] = color & 0x1F;
        color >>= 5;
        dst[4] = color & 0x1F;
        color >>= 5;
        dst[5] = color & 0x1F;
        dst += 6;
        remaining -= 6;
    }
    LoadImage(&rect, (u_long*)D_801459FC);
    if (count & 3) {
        count += 4 - count % 4;
    }
    D_801459FC += count;
}
