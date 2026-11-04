#include "engine/slus/slus.h"

/* copies 0x20 halfwords of the selected record field into dst and dst +
 * 0x4000, then marks the copy complete.
 */
MATCH void GFX_StagePalette(u8* dst, s32 field) {
    u8* record;
    u8* table;
    u8* src;
    u8* second;
    s32 index;
    u16 value;

    record = (u8*)g_SpadWork->unk_4C;
    table  = record + *(u32*)(record + 4);
    src    = table + *(u32*)(table + (field & BYTE_MASK) * 4);
    second = dst + 0x4000;
    for (index = 0; index < 32; index++) {
        value      = *(u16*)src;
        *(u16*)dst = value;
        src += 2;
        dst += 2;
        *(u16*)second = value;
        second += 2;
    }
    g_GfxPalettePending = 1;
}
