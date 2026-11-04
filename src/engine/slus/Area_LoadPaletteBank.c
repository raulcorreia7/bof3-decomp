#include "engine/slus/slus.h"

/* Destination palette bank (AREA_PALETTE_WORK, the g_GraphicsPaletteDst of include/gfx/prim.h). The constant keeps the
 * lui+ori codegen the original binary uses for the bank. */

/* searches the palette records for the id g_FrameCount modulo the header word gives, copies the record's 0x20
 * bytes into the palette bank and raises the palette stage serial; a record id above the wanted id ends the search.
 */
MATCH void Area_LoadPaletteBank(u8* palette_list) {
    s32* dst;
    s32* src;
    s32  count;
    s32  id;
    u32  entry;
    u32  base;
    u8*  ptr;

    ptr = palette_list;
    id  = (s32)((u32)g_FrameCount % *(u16*)ptr) + 1;
    ptr += 4;
    if ((Area_TestCondition(*(s16*)ptr) << 24) != 0) {
        base = AREA_PALETTE_WORK;
        for (;;) {
            ptr += 4;
            entry = *(u32*)ptr;
            if (id == (s32)(entry >> 24)) {
                count = 0;
                dst   = (s32*)((((entry >> 4) & BYTE_MASK) << 9) + (((entry & 0xF) << 5) + base));
                src   = (s32*)((((entry >> 16) & BYTE_MASK) << 9) + (((entry >> 7) & 0x1E0) + base));
                do {
                    *dst = *src;
                    src += 1;
                    count += 1;
                    dst += 1;
                } while (count < 8);
                g_GfxPalettePending = 1;
                return;
            }
            if (id < (s32)(entry >> 24)) {
                break;
            }
        }
    }
}
