#include "game_00.h"

/* 8-byte record copied to the stack; read back as halfwords. */
MATCH void func_801C308C(s32 arg) {
    GameSeed        seed;
    volatile Actor* work;
    s32             index;
    s32             off;
    u32             base_dst;
    u32             page;
    u32             row;
    u32             addr_dst;
    u8              sel;

    seed     = D_80196014;
    index    = 1;
    work     = g_Task;
    /* CLUT block base as a literal keeps the lui+ori codegen. */
    base_dst = AREA_PALETTE_WORK;
    do {
        off = index << 1;
        sel = work->unk_27;
        index += 1;
        page                            = (sel >> 3) << 9;
        addr_dst                        = page + base_dst;
        row                             = (sel & 0x7) << 6;
        *(u16*)(off + (row + addr_dst)) = seed.cells[arg & BYTE_MASK];
    } while (index < 32);
    g_GfxPalettePending = 1;
    /* FAKE: hold cue arg after store. */
    FAKE_BARRIER();
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 8));
    g_Game.current->status.field.flags_12C.u8_value |= 8;
}
