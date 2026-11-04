#include "engine/slus/slus.h"

/* libgpu getTPage, and the texture-page layout of graph types 1 and 2. */
#define getTPageStandard(tp, abr, x, y)                                                                               \
    ((((tp) & 0x3) << 7) | (((abr) & 0x3) << 5) | (((y) & 0x100) >> 4) | (((x) & 0x3FF) >> 6) | (((y) & 0x200) << 2))
#define getTPageN(tp, abr, x, y) ((((tp) & 0x3) << 9) | (((abr) & 0x3) << 7) | (((y) >> 3) & 0x60) | (((x) >> 6) & 0xF))

/* Draws the entity of the scratchpad work record g_SpadWork: culls it against the 0x1C0 by 0x170 screen window
 * (setting or clearing the hidden bit 0x80 of the first byte), then queues its sprite cells. Plain cells go to
 * func_8014CF9C; flipped or scaled cells become FT4 primitives here, with the size row from D_8017F53C.
 */
MATCH void Area_DrawObjectSprite(void) {
    POLY_FT4*   prim;
    SpriteCell* cell;
    u8*         list;
    u8          count;
    u8          mode;
    u8          clip_x;
    u8          clip_y;
    s8          bank;
    u8          width;
    u8          height;
    s16         x;
    s16         y;
    s32         page;
    s32         tpage;
    s32         tint;
    u16         clut;

    if (g_SpadWork->flags_00 & ACTOR_FLAG_HIDDEN) {
        return;
    }
    if (!(g_SpadWork->flags_24 & 0x80) && g_SpadWork->unk_48 == 1) {
        if (g_SpadWork->unk_60 == 0) {
            g_SpadWork->unk_40 = 0;
            g_SpadWork->unk_44 = 0;
            return;
        }
        g_SpadWork->unk_40 = (0x4650000 / g_SpadWork->unk_60) & ~0xFF;
        g_SpadWork->unk_44 = (0x4650000 / g_SpadWork->unk_60) & ~0xFF;
    }
    if ((u16)(g_SpadWork->unk_2E + 0x40) > 0x1C0 || (u16)(g_SpadWork->unk_30 + 0x40) > 0x170) {
        g_SpadWork->flags_00 |= ACTOR_FLAG_OFFSCREEN;
        return;
    }
    g_SpadWork->flags_00 &= ~ACTOR_FLAG_OFFSCREEN;
    if (g_SpadWork->flags_24 & 8) {
        RECT* rect = (RECT*)g_GfxPrimCursor;
        g_GfxPrimCursor += sizeof(RECT);
        rect->x = 832;
        rect->y = 256;
        rect->w = 192;
        rect->h = 256;
        SetDrawArea((DR_AREA*)(rect + 1), rect);
        GFX_AddPrim(g_SpadWork->unk_29, sizeof(DR_AREA));
        g_SpadWork->unk_2E += 0x340;
        y                  = g_SpadWork->unk_30 + 0x10;
        g_SpadWork->unk_30 = y + (g_FrameBufferIndex ^ 1) * 0xF0;
    }
    list  = g_SpadWork->range_54.table + g_SpadWork->unk_5A;
    count = *list;
    cell  = (SpriteCell*)(list + 1);
    Area_BuildClut(&clut);
    for (; count != 0; cell++, count--) {
        mode = cell->size >> 7;
        if (g_SpadWork->unk_2A != 0) {
            mode |= 2;
        }
        if (g_SpadWork->unk_48 != 0) {
            mode |= 4;
        }
        if (mode == 0 || mode == 3) {
            Area_DrawSpriteCell(mode, cell, clut);
        } else {
            if (g_SpadWork->unk_48 != 0) {
                clip_x = (u32)(g_SpadWork->unk_40 + 0x1E000) > 0x3C000;
                clip_y = (u32)(g_SpadWork->unk_44 + 0x1E000) > 0x3C000;
            } else {
                clip_x = 0;
                clip_y = 0;
            }
            bank = 0;
            if (g_SpadWork->unk_28 != 0) {
                bank = -1;
                if (cell->u >= 0x28) {
                    bank = cell->u >= 0xA1;
                }
            }
            prim   = (POLY_FT4*)g_GfxPrimCursor;
            width  = g_SpriteSizes[cell->size & GFX_SPRITE_SIZE_MASK][0];
            height = g_SpriteSizes[cell->size & GFX_SPRITE_SIZE_MASK][1];
            SetPolyFT4(prim);
            if (mode == 1) {
                x        = g_SpadWork->unk_2E + (s8)cell->x;
                prim->x0 = x;
                prim->x1 = width + x;
                prim->u1 = cell->u - bank * 128 - 1;
                prim->u0 = prim->u1 + width;
            } else if (mode == 2) {
                x        = g_SpadWork->unk_2E - (s8)cell->x;
                prim->x0 = x;
                prim->x1 = x - width;
                prim->u0 = cell->u - bank * 128 - 1;
                prim->u1 = prim->u0 + width;
            } else if (mode == 4) {
                prim->x0 = g_SpadWork->unk_2E +
                           Area_RoundSpriteCoordinate((s8)cell->x * g_SpadWork->unk_40, g_SpadWork->unk_40);
                prim->x1 = prim->x0 + Area_RoundSpriteCoordinate(width * g_SpadWork->unk_40, g_SpadWork->unk_40);
                prim->u0 = cell->u - bank * 128;
                prim->u1 = prim->u0 + width - clip_x;
            } else if (mode == 6) {
                prim->x1 = g_SpadWork->unk_2E -
                           Area_RoundSpriteCoordinate((s8)cell->x * g_SpadWork->unk_40, g_SpadWork->unk_40);
                prim->x0 = prim->x1 - Area_RoundSpriteCoordinate(width * g_SpadWork->unk_40, g_SpadWork->unk_40);
                prim->u1 = clip_x + (cell->u - bank * 128 - 1);
                prim->u0 = prim->u1 + width - clip_x;
            } else if (mode == 5) {
                prim->x0 = g_SpadWork->unk_2E +
                           Area_RoundSpriteCoordinate((s8)cell->x * g_SpadWork->unk_40, g_SpadWork->unk_40);
                prim->x1 = prim->x0 + Area_RoundSpriteCoordinate(width * g_SpadWork->unk_40, g_SpadWork->unk_40);
                prim->u1 = clip_x + (cell->u - bank * 128 - 1);
                prim->u0 = prim->u1 + width - clip_x;
            } else if (mode == 7) {
                prim->x1 = g_SpadWork->unk_2E -
                           Area_RoundSpriteCoordinate((s8)cell->x * g_SpadWork->unk_40, g_SpadWork->unk_40);
                prim->x0 = prim->x1 - Area_RoundSpriteCoordinate(width * g_SpadWork->unk_40, g_SpadWork->unk_40);
                prim->u0 = cell->u - bank * 128;
                prim->u1 = prim->u0 + width - clip_x;
            }
            prim->x2 = prim->x0;
            prim->x3 = prim->x1;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            if (mode & 4) {
                prim->y0 = g_SpadWork->unk_30 +
                           Area_RoundSpriteCoordinate((s8)cell->y * g_SpadWork->unk_44, g_SpadWork->unk_44);
                prim->y2 = prim->y0 + Area_RoundSpriteCoordinate(height * g_SpadWork->unk_44, g_SpadWork->unk_44);
            } else {
                y        = g_SpadWork->unk_30 + (s8)cell->y;
                prim->y0 = y;
                prim->y2 = height + y;
            }
            prim->y1 = prim->y0;
            prim->y3 = prim->y2;
            prim->v0 = g_SpadWork->unk_26 + cell->v;
            prim->v2 = prim->v0 + height - clip_y;
            prim->v1 = prim->v0;
            prim->v3 = prim->v2;
            tint     = g_SpadWork->tint.bytes.unk_5D - 0x80;
            prim->r0 = tint;
            tint     = g_SpadWork->tint.bytes.unk_5E - 0x80;
            prim->g0 = tint;
            tint     = g_SpadWork->tint.bytes.unk_5F - 0x80;
            prim->b0 = tint;
            if (GetGraphType() == 1 || GetGraphType() == 2) {
                page  = g_SpadWork->unk_25 + bank;
                tpage = getTPageN(g_SpadWork->unk_28 ? 1 : 0, g_SpadWork->tint.bytes.flags, (page % 16) << 6,
                                  (page / 16) << 8);
            } else {
                page  = g_SpadWork->unk_25 + bank;
                tpage = getTPageStandard(g_SpadWork->unk_28 ? 1 : 0, g_SpadWork->tint.bytes.flags, (page % 16) << 6,
                                         (page / 16) << 8);
            }
            prim->tpage = tpage;
            prim->clut  = clut;
            SetSemiTrans(prim, (g_SpadWork->flags_00 & ACTOR_FLAG_SEMI_TRANSPARENT) != 0);
            GFX_AddPrim(g_SpadWork->unk_29, sizeof(POLY_FT4));
        }
    }
    if (g_SpadWork->flags_24 & 8) {
        RECT* rect = (RECT*)g_GfxPrimCursor;
        g_GfxPrimCursor += sizeof(RECT);
        *rect = *(RECT*)(g_GfxCurrentDisplayFrame + 0x14);
        SetDrawArea((DR_AREA*)g_GfxPrimCursor, rect);
        GFX_AddPrim(g_SpadWork->unk_29, sizeof(DR_AREA));
    }
}
