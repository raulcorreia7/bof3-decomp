#include "game_00.h"

/* Source and destination CLUT blocks. Literal addresses keep the
 * lui+ori codegen the original binary uses for these blocks. */
#define CLUT_BLOCK_SRC 0x80033800u

MATCH void func_801C3154(void) {
    volatile Actor* work;
    u32             base_dst;
    u32             base_src;
    u32             page;
    u32             row;
    u32             addr_dst;
    s32             index;
    s32             off;
    u8              sel;

    if ((g_Game.current->status.field.flags_12C.u8_value & 0x8) != 0) {
        index    = 1;
        work     = g_Task;
        base_dst = AREA_PALETTE_WORK;
        base_src = CLUT_BLOCK_SRC;
        do {
            off = index << 1;
            sel = work->unk_27;
            index += 1;
            page                            = (sel >> 3) << 9;
            addr_dst                        = page + base_dst;
            row                             = (sel & 0x7) << 6;
            *(u16*)(off + (row + addr_dst)) = *(const u16*)(off + (row + (page + base_src)));
        } while (index < 32);
        g_GfxPalettePending = 1;
        g_Game.current->status.field.flags_12C.u8_value &= 0xF7u;
    }
}
