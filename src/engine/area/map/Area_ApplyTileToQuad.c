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

/* The tile table rectangle is AreaTileRect (include/area/area.h); its box view
 * reads the size pair and the page corner as the signed halfword retail loads
 * with `lh` before masking the low byte. */

/* func_80155560 */
#ifdef NON_MATCHING
NON_MATCHING s32 Area_ApplyTileToQuad(u32 part_word, POLY_FT4* prim, s32 mode) {
    AreaTileCorner uv[5];
    AreaTileRect*  rect;
    POLY_FT4*      poly;
    s32            word = part_word;
    s32            flag;
    s32            sel;
    s32            pal;
    s32            clut;
    s32            tpage;
    s32            swap;
    s32            i;
    s32            u;
    s32            v;
    u8             lum;

    flag = !(word >> 31);
    sel  = (word >> 28) & 3;
    if (word & 0xF00) {
        if (word & 0x800) {
            rect       = (AreaTileRect*)((word & 0x7FF) * 8 + MAP_BUNDLE_BASE);
            rect       = (AreaTileRect*)(g_AreaMapBundle.tile_offsets[sel][1] * 4 + (u32)rect);
            u          = rect->fields.u;
            v          = rect->box.v & 0xFF;
            uv[1].at.u = u;
            uv[1].at.v = v;
            uv[2].at.u = rect->box.width;
            uv[2].at.v = rect->box.height;
            rect++;
            u          = rect->fields.u;
            v          = rect->box.v & 0xFF;
            uv[3].at.u = u;
            uv[3].at.v = v;
            uv[4].at.u = rect->box.width;
            uv[4].at.v = rect->box.height;
        } else {
            rect       = (AreaTileRect*)((word & 0xFF) * 4 + MAP_BUNDLE_BASE);
            rect       = (AreaTileRect*)(g_AreaMapBundle.tile_offsets[sel][0] * 4 + (u32)rect);
            u          = rect->fields.u;
            v          = rect->box.v & 0xFF;
            uv[1].at.u = u;
            uv[3].at.u = u;
            uv[1].at.v = v;
            uv[2].at.v = v;
            uv[2].at.u = u + rect->box.width;
            uv[4].at.u = u + rect->box.width;
            uv[3].at.v = v + rect->box.height;
            uv[4].at.v = v + rect->box.height;
        }
    } else {
        u          = (word & 0xF) << 4;
        v          = word & 0xF0;
        uv[1].at.u = u;
        uv[3].at.u = u;
        uv[1].at.v = v;
        uv[2].at.v = v;
        uv[2].at.u = u | 0xF;
        uv[4].at.u = u | 0xF;
        uv[3].at.v = v | 0xF;
        uv[4].at.v = v | 0xF;
    }
    if (word & 0x40000) {
        swap       = uv[3].word;
        uv[3].word = uv[4].word;
        uv[4].word = uv[2].word;
        uv[2].word = uv[1].word;
        uv[1].word = swap;
    }
    if (word & 0x10000) {
        swap       = uv[1].word;
        uv[1].word = uv[2].word;
        uv[2].word = swap;
        swap       = uv[3].word;
        uv[3].word = uv[4].word;
        uv[4].word = swap;
    }
    if (word & 0x20000) {
        swap       = uv[1].word;
        uv[1].word = uv[3].word;
        uv[3].word = swap;
        swap       = uv[2].word;
        uv[2].word = uv[4].word;
        uv[4].word = swap;
    }
    pal  = (word >> 24) & 0xF;
    clut = (pal * flag + 0x1E3) << 6;
    if (!flag) {
        clut |= pal;
    }
    lum   = (word >> 16) & 0xF8;
    tpage = getTPage(flag, word >> 12, (sel << 7) + SCREEN_WIDTH, 256);
    poly  = prim;
    for (i = 0; i < mode; i++, poly++) {
        SetSemiTrans(poly, (word >> 15) & 1);
        setRGB0(poly, lum, lum, lum);
        poly->clut  = clut;
        poly->tpage = tpage;
        setUV4(poly, uv[1].at.u, uv[1].at.v, uv[2].at.u, uv[2].at.v, uv[3].at.u, uv[3].at.v, uv[4].at.u, uv[4].at.v);
    }
}
#else
INCLUDE_ASM(Area_ApplyTileToQuad);
#endif
