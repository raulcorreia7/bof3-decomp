#include "engine/slus/slus.h"

/* walks the bundle record list from g_AreaMapBundle.list_base_22: a 0x80 record picks the sub-record that the g_FrameCount
 * serial modulo the low byte selects and copies its eight palette words to g_GraphicsPaletteDst, raising the palette
 * stage serial; each record advances by its +2 size byte.
 */
MATCH void Area_CyclePalette(void) {
    u32* record;
    u32* dst;
    u32* src;
    u32  header;
    u32  entry;
    s32  select;
    s32  i;
    u32  tag;
    u32  kind;

    record = (u32*)MAP_BUNDLE_BASE + g_AreaMapBundle.list_base_22;
    while (*record != 0) {
        header = *record;
        kind   = header >> 24;
        tag    = 0x80;
        /* FAKE: retail reloads the 0x80 tag each record. */
        MATCH_FAKE_OPAQUE(tag);
        if (kind == tag) {
            select = (s32)((u32)g_FrameCount % (header & BYTE_MASK)) + 1;
            src    = record + 1;
            do {
                entry = *src++;
            } while ((s32)(entry >> 24) < select);
            i   = 0;
            dst = (u32*)((u8*)g_GraphicsPaletteDst + (((entry >> 4) & BYTE_MASK) << 9) + ((entry & 0xF) << 5));
            src = (u32*)((u8*)g_GraphicsPaletteDst + (((entry >> 16) & BYTE_MASK) << 9) + ((entry >> 7) & 0x1E0));
            do {
                *dst++ = *src++;
                i++;
            } while (i < 8);
            g_GfxPalettePending = 1;
        }
        record += ((u8*)record)[2];
    }
}
