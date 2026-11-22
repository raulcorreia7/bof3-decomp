#include "engine/slus/slus.h"

/* programs the sprite rectangle for the current stream slot from
 * its record entry and uploads the slot's image when it fits the screen.
 */
MATCH void EMI_SectorUploadImage(void) {
    s8* idxp;
    s8  index;
    u8* base;
    u8* entry;
    u8  v;
    s16 h;

    g_EmiUploadRect.w = 0x20;
    g_EmiUploadRect.h = 0x20;
    idxp              = &D_80146488;
    h                 = *idxp;
    index             = h;
    base              = (u8*)idxp + 0x30;
    entry             = base;
    entry += index << 2;
    v                 = entry[3];
    g_EmiUploadRect.x = (v << 5);
    h                 = (*(u16*)(entry + 2) & 0x3F);
    g_EmiUploadRect.y = (h << 5);
    if (((v << 5) < 0x3E9) && ((h << 5) < 0x1F5)) {
        LoadImage(&g_EmiUploadRect, (u_long*)(g_EmiRingBase + (index << 11)));
    }
}
