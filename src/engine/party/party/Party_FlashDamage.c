#include "engine/game/00/game_00.h"

/* 8-byte record copied to the stack; read back as halfwords. */
/* func_801C308C */
/* Floods the field actor's palette row with a damage colour, plays the common sound effect 8 and sets bit 3 of the member's field flags. */
MATCH void Party_FlashDamage(s32 color_index) {
    PaletteColors   seed;
    volatile Actor* work;
    s32             index;
    s32             off;
    u32             base_dst;
    u32             page;
    u32             row;
    u32             addr_dst;
    u8              sel;

    seed     = g_PartyDamageColors;
    index    = 1;
    work     = SELF(Actor);
    /* CLUT block base as a literal keeps the lui+ori codegen. */
    base_dst = AREA_PALETTE_WORK;
    do {
        off = index << 1;
        sel = work->clut_select;
        index += 1;
        page                            = (sel >> 3) << 9;
        addr_dst                        = page + base_dst;
        row                             = (sel & 0x7) << 6;
        *(u16*)(off + (row + addr_dst)) = seed.colors[color_index & BYTE_MASK];
    } while (index < 32);
    g_GfxPalettePending = 1;
    /* FAKE: hold cue arg after store. */
    FAKE_BARRIER();
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 8));
    g_Game.current->status.field.flags.unsigned_value |= 8;
}
