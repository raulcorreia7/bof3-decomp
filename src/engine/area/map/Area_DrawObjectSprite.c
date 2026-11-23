#include "engine/slus/slus.h"

/* Draws the entity of the scratchpad work record g_Task: culls it against the 0x1C0 by 0x170 screen window
 * (setting or clearing the hidden bit 0x80 of the first byte), then queues its sprite cells. Plain cells go to
 * func_8014CF9C; flipped or scaled cells become FT4 primitives here, with the size row from g_SpriteSizes.
 */
MATCH void Area_DrawObjectSprite(void) {
    POLY_FT4*   prim;
    SpriteCell* cell;
    u8*         list;
    u8          count;
    u8          mode;
    u8          clip_x;
    u8          clip_y;
    s8          page_offset;
    u8          width;
    u8          height;
    s16         x;
    s16         y;
    s32         page;
    s32         tpage;
    s32         tint;
    u16         clut;

    if (TASK(Actor)->header.flags & ACTOR_FLAG_HIDDEN) {
        return;
    }
    if (!(TASK(Actor)->active_flags & 0x80) && TASK(Actor)->unk_48 == 1) {
        if (TASK(Actor)->unk_60 == 0) {
            TASK(Actor)->scale.x = 0;
            TASK(Actor)->scale.y = 0;
            return;
        }
        TASK(Actor)->scale.x = (0x4650000 / TASK(Actor)->unk_60) & ~0xFF;
        TASK(Actor)->scale.y = (0x4650000 / TASK(Actor)->unk_60) & ~0xFF;
    }
    if ((u16)(TASK(Actor)->screen_x + 0x40) > 0x1C0 || (u16)(TASK(Actor)->screen_y + 0x40) > 0x170) {
        TASK(Actor)->header.flags |= ACTOR_FLAG_OFFSCREEN;
        return;
    }
    TASK(Actor)->header.flags &= ~ACTOR_FLAG_OFFSCREEN;
    if (TASK(Actor)->active_flags & 0x8) {
        RECT* rect = (RECT*)g_GfxPrimCursor;
        g_GfxPrimCursor += sizeof(RECT);
        rect->x = 832;
        rect->y = 256;
        setWH(rect, 192, 256);
        SetDrawArea((DR_AREA*)(rect + 1), rect);
        GFX_AddPrim(TASK(Actor)->draw_layer, sizeof(DR_AREA));
        TASK(Actor)->screen_x += 0x340;
        y                     = TASK(Actor)->screen_y + 0x10;
        TASK(Actor)->screen_y = y + (g_GfxBufferIndex ^ 0x1) * 0xF0;
    }
    list  = TASK(Actor)->range_54.table + TASK(Actor)->frame_cells;
    count = *list;
    cell  = (SpriteCell*)(list + 1);
    Area_BuildClut(&clut);
    for (; count != 0; cell++, count--) {
        mode = cell->size >> 7;
        if (TASK(Actor)->mirror != 0) {
            mode |= 2;
        }
        if (TASK(Actor)->unk_48 != 0) {
            mode |= 4;
        }
        if (mode == 0 || mode == 3) {
            Area_DrawSpriteCell(mode, cell, clut);
        } else {
            if (TASK(Actor)->unk_48 != 0) {
                clip_x = (u32)(TASK(Actor)->scale.x + 0x1E000) > 0x3C000;
                clip_y = (u32)(TASK(Actor)->scale.y + 0x1E000) > 0x3C000;
            } else {
                clip_x = 0;
                clip_y = 0;
            }
            page_offset = 0;
            if (TASK(Actor)->palette_8bit != PALETTE_TYPE_CELL) {
                page_offset = -1;
                if (cell->u >= 0x28) {
                    page_offset = cell->u >= 0xA1;
                }
            }
            prim   = (POLY_FT4*)g_GfxPrimCursor;
            width  = g_SpriteSizes[cell->size & GFX_SPRITE_SIZE_MASK][0];
            height = g_SpriteSizes[cell->size & GFX_SPRITE_SIZE_MASK][1];
            SetPolyFT4(prim);
            if (mode == 1) {
                x        = TASK(Actor)->screen_x + (s8)cell->x;
                prim->x0 = x;
                prim->x1 = width + x;
                prim->u1 = cell->u - page_offset * 128 - 1;
                prim->u0 = prim->u1 + width;
            } else if (mode == 2) {
                x        = TASK(Actor)->screen_x - (s8)cell->x;
                prim->x0 = x;
                prim->x1 = x - width;
                prim->u0 = cell->u - page_offset * 128 - 1;
                prim->u1 = prim->u0 + width;
            } else if (mode == 4) {
                prim->x0 = TASK(Actor)->screen_x + Area_RoundSpriteCoordinate((s8)cell->x * TASK(Actor)->scale.x, TASK(Actor)->scale.x);
                prim->x1 = prim->x0 + Area_RoundSpriteCoordinate(width * TASK(Actor)->scale.x, TASK(Actor)->scale.x);
                prim->u0 = cell->u - page_offset * 128;
                prim->u1 = prim->u0 + width - clip_x;
            } else if (mode == 6) {
                prim->x1 = TASK(Actor)->screen_x - Area_RoundSpriteCoordinate((s8)cell->x * TASK(Actor)->scale.x, TASK(Actor)->scale.x);
                prim->x0 = prim->x1 - Area_RoundSpriteCoordinate(width * TASK(Actor)->scale.x, TASK(Actor)->scale.x);
                prim->u1 = clip_x + (cell->u - page_offset * 128 - 1);
                prim->u0 = prim->u1 + width - clip_x;
            } else if (mode == 5) {
                prim->x0 = TASK(Actor)->screen_x + Area_RoundSpriteCoordinate((s8)cell->x * TASK(Actor)->scale.x, TASK(Actor)->scale.x);
                prim->x1 = prim->x0 + Area_RoundSpriteCoordinate(width * TASK(Actor)->scale.x, TASK(Actor)->scale.x);
                prim->u1 = clip_x + (cell->u - page_offset * 128 - 1);
                prim->u0 = prim->u1 + width - clip_x;
            } else if (mode == 7) {
                prim->x1 = TASK(Actor)->screen_x - Area_RoundSpriteCoordinate((s8)cell->x * TASK(Actor)->scale.x, TASK(Actor)->scale.x);
                prim->x0 = prim->x1 - Area_RoundSpriteCoordinate(width * TASK(Actor)->scale.x, TASK(Actor)->scale.x);
                prim->u0 = cell->u - page_offset * 128;
                prim->u1 = prim->u0 + width - clip_x;
            }
            prim->x2 = prim->x0;
            prim->x3 = prim->x1;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            if (mode & 0x4) {
                prim->y0 = TASK(Actor)->screen_y + Area_RoundSpriteCoordinate((s8)cell->y * TASK(Actor)->scale.y, TASK(Actor)->scale.y);
                prim->y2 = prim->y0 + Area_RoundSpriteCoordinate(height * TASK(Actor)->scale.y, TASK(Actor)->scale.y);
            } else {
                y        = TASK(Actor)->screen_y + (s8)cell->y;
                prim->y0 = y;
                prim->y2 = height + y;
            }
            prim->y1    = prim->y0;
            prim->y3    = prim->y2;
            prim->v0    = TASK(Actor)->sheet_row + cell->v;
            prim->v2    = prim->v0 + height - clip_y;
            prim->v1    = prim->v0;
            prim->v3    = prim->v2;
            tint        = TASK(Actor)->tint.bytes.rgb.r - 0x80;
            prim->r0    = tint;
            tint        = TASK(Actor)->tint.bytes.rgb.g - 0x80;
            prim->g0    = tint;
            tint        = TASK(Actor)->tint.bytes.rgb.b - 0x80;
            prim->b0    = tint;
            /* The page is assigned inside the macro: retail computes it once in each branch. */
            tpage       = getTPage(TASK(Actor)->palette_8bit ? 1 : 0, TASK(Actor)->tint.bytes.flags, (page % 16) << 6, ((page = TASK(Actor)->sheet_page + page_offset) / 16) << 8);
            prim->tpage = tpage;
            prim->clut  = clut;
            SetSemiTrans(prim, (TASK(Actor)->header.flags & ACTOR_FLAG_SEMI_TRANSPARENT) != 0);
            GFX_AddPrim(TASK(Actor)->draw_layer, sizeof(POLY_FT4));
        }
    }
    if (TASK(Actor)->active_flags & 0x8) {
        RECT* rect = (RECT*)g_GfxPrimCursor;
        g_GfxPrimCursor += sizeof(RECT);
        *rect = g_GfxCurrentBuffer->draw.clip;
        SetDrawArea((DR_AREA*)g_GfxPrimCursor, rect);
        GFX_AddPrim(TASK(Actor)->draw_layer, sizeof(DR_AREA));
    }
}
