#include "engine/slus/slus.h"

/* programs the sprite rectangle for the current stream slot from
 * its record entry and uploads the slot's image when it fits the screen.
 */
MATCH void EMI_LoaderUploadSector(void) {
    s8*   idxp;
    s8    index;
    u8*   base;
    u8*   entry;
    RECT* rect;
    u8    v;
    s16   h;

    D_80146850[0] = 0x20;
    D_80146852    = 0x20;
    idxp          = &D_80146488;
    h             = *idxp;
    index         = h;
    base          = (u8*)idxp + 0x30;
    entry         = base;
    entry += index << 2;
    v              = entry[3];
    D_80146850[-2] = (s16)(v << 5);
    rect           = (RECT*)&D_80146850[-2];
    h              = (u16)(*(u16*)(entry + 2) & 0x3F);
    D_8014684E     = (s16)(h << 5);
    if (((v << 5) < 0x3E9) && ((h << 5) < 0x1F5)) {
        LoadImage(rect, (u_long*)(g_EmiRingBase + (index << 11)));
    }
}
