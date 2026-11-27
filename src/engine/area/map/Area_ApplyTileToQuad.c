#include "engine/slus/slus.h"

/* One texture corner of a drawn quad: the u and v to store, or the whole pair to swap. Retail
 * keeps four of them eight bytes apart at sp+0x18, one cell above the array it declares. */
typedef union AreaTileCorner {
    s32 word;

    struct {
        u16 u;
        u16 v;
    } at;

    RECT rect;
} AreaTileCorner;

/* Each tile table entry is one word: u in its signed top byte, then v, then the width and height
 * (table A) or the far corner (table B). */

/* func_80155560 */
MATCH s32 Area_ApplyTileToQuad(u32 part_word, POLY_FT4* prim, s32 mode) {
    AreaTileCorner uv[5];
    s32*           rect;
    AreaMapBundle* bundle;
    POLY_FT4*      poly;
    s32            flag;
    s32            sel;
    s32            pal;
    s32            clut;
    s32            tpage;
    s32            swap;
    s32            i;
    s32            u;
    s32            v;
    s32            lum;

    flag = !((s32)part_word >> 31);
    sel  = ((s32)part_word >> 28) & 3;
    if (part_word & 0xF00) {
        if (part_word & 0x800) {
            bundle     = AREA_MAP_BUNDLE;
            rect       = (s32*)(bundle->tile_offsets[sel][1] * 4 + ((part_word & 0x7FF) * 8 + (u32)bundle));
            uv[1].at.u = *rect >> 24;
            uv[1].at.v = (*rect >> 16) & 0xFF;
            uv[2].at.u = (*rect >> 8) & 0xFF;
            uv[2].at.v = *rect & 0xFF;
            rect++;
            uv[3].at.u = *rect >> 24;
            uv[3].at.v = (*rect >> 16) & 0xFF;
            uv[4].at.u = (*rect >> 8) & 0xFF;
            uv[4].at.v = *rect & 0xFF;
        } else {
            bundle     = AREA_MAP_BUNDLE;
            rect       = (s32*)(bundle->tile_offsets[sel][0] * 4 + ((part_word & 0xFF) * 4 + (u32)bundle));
            uv[1].at.u = uv[3].at.u = *rect >> 24;
            uv[1].at.v = uv[2].at.v = (*rect >> 16) & 0xFF;
            uv[2].at.u = uv[4].at.u = uv[1].at.u + ((*rect >> 8) & 0xFF);
            uv[3].at.v = uv[4].at.v = uv[1].at.v + (*rect & 0xFF);
        }
    } else {
        u          = (part_word & 0xF) << 4;
        v          = part_word & 0xF0;
        uv[1].at.u = uv[3].at.u = u;
        uv[1].at.v = uv[2].at.v = v;
        uv[2].at.u = uv[4].at.u = u | 0xF;
        uv[3].at.v = uv[4].at.v = v | 0xF;
    }
    if (part_word & 0x40000) {
        swap       = uv[1].word;
        uv[1].word = uv[3].word;
        uv[3].word = uv[4].word;
        uv[4].word = uv[2].word;
        uv[2].word = swap;
    }
    if (part_word & 0x10000) {
        swap       = uv[1].word;
        uv[1].word = uv[2].word;
        uv[2].word = swap;
        swap       = uv[3].word;
        uv[3].word = uv[4].word;
        uv[4].word = swap;
    }
    if (part_word & 0x20000) {
        swap       = uv[1].word;
        uv[1].word = uv[3].word;
        uv[3].word = swap;
        swap       = uv[2].word;
        uv[2].word = uv[4].word;
        uv[4].word = swap;
    }
    pal  = ((s32)part_word >> 24) & 0xF;
    clut = (pal * flag + 0x1E3) << 6;
    lum  = ((s32)part_word >> 16) & 0xF8;
    if (!flag) {
        clut |= pal;
    }
    tpage = getTPage(flag, (s32)part_word >> 12, (sel << 7) + SCREEN_WIDTH, 256);
    for (i = 0; i < mode; i++) {
        poly = &prim[i];
        SetSemiTrans(poly, ((s32)part_word >> 15) & 1);
        poly->r0 = poly->g0 = poly->b0 = lum;
        poly->clut                     = clut;
        poly->tpage                    = tpage;
        setUV4(poly, uv[1].at.u, uv[1].at.v, uv[2].at.u, uv[2].at.v, uv[3].at.u, uv[3].at.v, uv[4].at.u, uv[4].at.v);
    }
}
