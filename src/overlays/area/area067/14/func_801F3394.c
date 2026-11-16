#include "area067_14.h"

MATCH void func_801F3394(AreaRippleQuad* quad) {
    TILE_1* tile;
    s32     radius2;
    s32     half;
    s16     i;
    s16     r;

    GFX_SET_DRAW_MODE(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100));
    Area_AddCellPrim(D_801F53A0, D_801F53A4, 4, sizeof(DR_MODE));

    r = quad->radius >> 2;
    i = -r;
    if (r >= i) {
        radius2 = r * r;
        do {
            half = SquareRoot0(radius2 - i * i);
            tile = GFX_CURSOR(TILE_1);
            SetTile1(tile);
            SetSemiTrans(tile, 1);
            tile->x0                 = quad->x + half;
            /* kept: the tile's y0 at 0xA; the field store schedules into the cell call's delay slot. */
            *(s16*)&((u8*)tile)[0xA] = quad->y + i;
            setRGB0(tile, 0x40, 0x40, 0x40);
            Area_AddCellPrim(D_801F53A0, D_801F53A4, 4, sizeof(TILE_1));
            tile++;
            *tile                    = tile[-1];
            /* kept: the second tile's x0 at 0x8; the field store schedules into the cell call's delay slot. */
            *(s16*)&((u8*)tile)[0x8] = quad->x - half;
            Area_AddCellPrim(D_801F53A0, D_801F53A4, 4, sizeof(TILE_1));
            i++;
        } while (i <= r);
    }
    GFX_SET_DRAW_MODE(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100));
    Area_AddCellPrim(D_801F53A0, D_801F53A4, 4, sizeof(DR_MODE));
}
