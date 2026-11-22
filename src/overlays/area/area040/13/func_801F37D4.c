#include "area040_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F37D4(void) {
    POLY_F4* prim;
    s32      shade;
    s32      id;
    s32      x;
    u8       i;
    s32      j;

    for (i = 0; i < 4; i++) {
        j = 0;
        for (; j < 4; j++) {
            if ((u8)Area_CellGetCode((j & BYTE_MASK) + 0x94, (s16)(i + 0x20)) != 0x50) {
                continue;
            }
            x  = (u8)j + 0x94;
            id = Area_CellGetId(x, i + 0x20);
            if (id == 0) {
                continue;
            }
            prim = (POLY_F4*)g_GfxPrimCursor;
            SetPolyF4(prim);
            SetSemiTrans(prim, 1);
            setXY4(prim, g_AreaCellPrims[id][g_GfxBufferIndex ? 0 : 1].x0, g_AreaCellPrims[id][g_GfxBufferIndex ? 0 : 1].y0, g_AreaCellPrims[id][g_GfxBufferIndex ? 0 : 1].x1,
                   g_AreaCellPrims[id][g_GfxBufferIndex ? 0 : 1].y1, g_AreaCellPrims[id][g_GfxBufferIndex ? 0 : 1].x2, g_AreaCellPrims[id][g_GfxBufferIndex ? 0 : 1].y2,
                   g_AreaCellPrims[id][g_GfxBufferIndex ? 0 : 1].x3, g_AreaCellPrims[id][g_GfxBufferIndex ? 0 : 1].y3);
            shade = (s32)((g_FrameCount >> 1) & 0xF) - 8;
            if (shade < 0) {
                shade = -shade;
            }
            shade *= 31;
            prim->b0 = shade;
            prim->g0 = shade;
            prim->r0 = shade;
            Area_CellAddPrim(x << 16, (i + 0x20) << 16, 0, sizeof(POLY_F4));
        }
    }
}
#else
INCLUDE_ASM(func_801F37D4);
#endif
