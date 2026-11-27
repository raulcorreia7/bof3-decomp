#include "engine/slus/slus.h"

/* FAKE: reload the scratch cursor cell through v0. */
#define SPAD_CURSOR     ((Actor*)SPAD_CURSOR_REF)
#define SPAD_CURSOR_REF (scratch_base = (u8*)SP(0u), *((void* volatile*)(scratch_base + 0x44u)))

/* draws one status sprite from the scratch cursor: selects the draw
 * mode by graph type, sets the texture from the cell record, offsets x by mirror,
 * selects the clut by clut and appends the primitive.
 */
MATCH void Area_DrawSpriteCell(s32 mirror, SpriteCell* cell, u16 clut) {
    u16         tpage;
    s32         delta;
    SPRT*       sprite;
    u8*         scratch_base;
    /* FAKE: copies of the arguments take the s1/s3/s2 homes in retail order. */
    SpriteCell* sprite_cell   = cell;
    s32         sprite_mirror = mirror;
    s16         sprite_clut   = clut;

    tpage = getTPage(SELF(Actor)->palette_8bit != PALETTE_TYPE_CELL, SELF(Actor)->tint.bytes.flags, SELF(Actor)->sheet_page << 6, (SELF(Actor)->sheet_page >> 4) << 8);
    GFX_ADD_LAYER_DRAW_MODE(SPAD_CURSOR->draw_layer, tpage);
    sprite = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprite);
    setWH(sprite, g_SpriteSizes[sprite_cell->size & GFX_SPRITE_SIZE_MASK][0], g_SpriteSizes[sprite_cell->size & GFX_SPRITE_SIZE_MASK][1]);
    sprite->y0 = SPAD_CURSOR->screen_y + (s8)sprite_cell->y;
    setUV0(sprite, sprite_cell->u, SPAD_CURSOR->sheet_row + sprite_cell->v);
    delta        = SPAD_CURSOR->tint.bytes.rgb.r - 0x80;
    sprite->r0   = delta;
    delta        = SPAD_CURSOR->tint.bytes.rgb.g - 0x80;
    sprite->g0   = delta;
    delta        = SPAD_CURSOR->tint.bytes.rgb.b - 0x80;
    sprite->b0   = delta;
    sprite->clut = sprite_clut;
    delta        = sprite_mirror & BYTE_MASK;
    if (!delta) {
        sprite->x0 = SPAD_CURSOR->screen_x + (s8)sprite_cell->x;
    } else {
        sprite->x0 = (SPAD_CURSOR->screen_x - (s8)sprite_cell->x) - sprite->w;
    }
    SetSemiTrans(sprite, (SPAD_CURSOR->header.flags >> 5) & 0x1);
    GFX_AddPrim(SPAD_CURSOR->draw_layer, sizeof(SPRT));
}
