#include "engine/slus/slus.h"

/* FAKE: reload the scratch cursor cell through v0. */
#define SPAD_CURSOR     ((Actor*)SPAD_CURSOR_REF)
#define SPAD_CURSOR_REF (scratch_base = (u8*)SP(0u), *(MATCH_VOLATILE_PTR(void* volatile, scratch_base + 0x44u)))

/* draws one status sprite from the scratch cursor: selects the draw
 * mode by graph type, sets the texture from the cell record, offsets x by mirror,
 * selects the clut by clut and appends the primitive.
 */
MATCH void Area_DrawSpriteCell(s32 mirror, SpriteCell* cell, u16 clut) {
    /* FAKE: keep the masked bit in a2. */
    MATCH_FAKE_PIN(s32, mode_bit, "a2");
    /* FAKE: keep the shifted flags in a3. */
    MATCH_FAKE_PIN(s32, mode_flags, "a3");
    /* FAKE: keep the shifted byte in v0. */
    MATCH_FAKE_PIN(s32, draw_value, "v0");
    s32 mode_bits;
    /* FAKE: reuse the retail a0 value for input, pointer, and output. */
    MATCH_FAKE_PIN(s32, scratch, "a0");
    s32         packed;
    Actor*      work;
    s32         delta;
    SPRT*       sprite;
    u8*         scratch_base;
    /* FAKE: copies of the arguments take the s1/s3/s2 homes in retail order. */
    SpriteCell* sprite_cell   = cell;
    s32         sprite_mirror = mirror;
    s16         sprite_clut   = clut;

    if ((GetGraphType() == 1) || (GetGraphType() == 2)) {
        work       = g_SpadWork;
        draw_value = work->tint.bytes.flags;
        mode_bit   = (draw_value & 3) << 7;
        scratch    = work->unk_25;
        draw_value = scratch * 2;
        packed     = draw_value & 0x60;
        /* FAKE: keep the mode read after its masks. */
        MATCH_FAKE_BARRIER();
        scratch = scratch & 0xF;
        if (work->unk_28 != 0) {
            draw_value = packed | 0x200;
            draw_value = mode_bit | draw_value;
        } else {
            draw_value = mode_bit | packed;
        }
    } else {
        scratch    = (s32)g_SpadWork;
        draw_value = ((Actor*)scratch)->tint.bytes.flags;
        mode_flags = (draw_value & 3) << 5;
        packed     = ((Actor*)scratch)->unk_25;
        draw_value = ((u32)packed >> 4) << 8;
        mode_bits  = draw_value & 0x100;
        /* FAKE: hide the masked bit's range so the shift stays arithmetic. */
        MATCH_FAKE_OPAQUE(mode_bits);
        mode_bit   = mode_bits >> 4;
        packed     = packed & 0xF;
        draw_value = draw_value & 0x200;
        /* FAKE: keep the mode read after its masks. */
        MATCH_FAKE_BARRIER();
        mode_bits = ((Actor*)scratch)->unk_28;
        scratch   = draw_value * 4;
        if (mode_bits != 0) {
            draw_value = mode_bit | 0x80;
            draw_value = mode_flags | draw_value;
        } else {
            draw_value = mode_flags | mode_bit;
        }
        draw_value |= packed;
    }
    draw_value |= scratch;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, draw_value, NULL);
    GFX_AddPrim((u32)SPAD_CURSOR->unk_29, 0xCU);
    sprite = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprite);
    sprite->w    = g_SpriteSizes[sprite_cell->size & GFX_SPRITE_SIZE_MASK][0];
    sprite->h    = g_SpriteSizes[sprite_cell->size & GFX_SPRITE_SIZE_MASK][1];
    sprite->y0   = SPAD_CURSOR->unk_30 + (s8)sprite_cell->y;
    sprite->u0   = sprite_cell->u;
    sprite->v0   = SPAD_CURSOR->unk_26 + sprite_cell->v;
    delta        = SPAD_CURSOR->tint.bytes.unk_5D - 0x80;
    sprite->r0   = delta;
    delta        = SPAD_CURSOR->tint.bytes.unk_5E - 0x80;
    sprite->g0   = delta;
    delta        = SPAD_CURSOR->tint.bytes.unk_5F - 0x80;
    sprite->b0   = delta;
    sprite->clut = sprite_clut;
    delta        = sprite_mirror & BYTE_MASK;
    if (!delta) {
        sprite->x0 = SPAD_CURSOR->unk_2E + (s8)sprite_cell->x;
    } else {
        sprite->x0 = (SPAD_CURSOR->unk_2E - (s8)sprite_cell->x) - sprite->w;
    }
    SetSemiTrans(sprite, (SPAD_CURSOR->flags_00 >> 5) & 1);
    GFX_AddPrim((u32)SPAD_CURSOR->unk_29, 0x14U);
}
