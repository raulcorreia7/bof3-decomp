#include "area189_13.h"

/* func_801F3378 */
MATCH void Area_SetCellTexture(s32 texture, POLY_FT4* prim) {
    SetSemiTrans(prim, 0);
    /* The channel stores keep retail's b0, g0, r0 order. */
    prim->b0    = 0x80;
    prim->g0    = 0x80;
    prim->r0    = 0x80;
    prim->clut  = (((texture >> 24) & 0xF) + 0x1E3) << 6;
    prim->tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    setUVWH(prim, (texture & 0xF) << 4, texture & 0xF0, 0xF, 0xF);
}
