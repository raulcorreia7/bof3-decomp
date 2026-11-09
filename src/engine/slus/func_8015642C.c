#include "engine/slus/slus.h"

/* draws the shadowed sprite pairs of the field object at obj, positioned from the (x, y) map cell: projects a
 * three-vertex rim to cull off-screen objects, then emits two textured quadrangles per part from the
 * D_8017F* tables, the second projection filling the first corners of both. */
#ifdef NON_MATCHING
NON_MATCHING void func_8015642C(u8* obj, s32 x, s32 y) {
    s32       depth;
    s32       flag;
    s32       order;
    s32       kind;
    s32       index;
    s32       part;
    s32       j;
    s32       off;
    s16       z;
    POLY_FT4* prim;
    POLY_FT4* p;

    if ((*(u32*)obj >> 28) != 0) {
        order = 6;
    } else {
        order = g_AreaDrawMode;
    }
    *(s32*)(D_1F800000)     = (x - 0x81) << 7;
    *(s32*)(D_1F800000 + 4) = (y - 0x80) << 7;
    kind                    = FIELD(u8, obj, 3u) & 0xF;
    index                   = kind - 1;
    z                       = -(Area_SampleHeight((x - 1) << 0x10, y << 0x10) / 2);
    *(s32*)(D_1F800000 + 8) = z;
    D_1F800014[2].vx        = *(s32*)(D_1F800000);
    D_1F800014[3].vx        = *(s32*)(D_1F800000);
    D_1F800014[3].vy        = *(s32*)(D_1F800000 + 4);
    D_1F800014[2].vy        = *(s32*)(D_1F800000 + 4);
    D_1F800014[3].vz        = z;
    D_1F800014[1].vz        = z;
    D_1F800014[2].vz        = z - D_8017F880[index];
    D_1F800014[0].vz        = z - D_8017F880[index];
    RotTransPers3(&D_1F800014[2], &D_1F800014[3], &D_1F800014[0], (s32*)D_1F800034, (s32*)((u8*)D_1F800034 + 4), (s32*)((u8*)D_1F800034 + 8), &depth, &flag);
    if (((u16)(D_1F800034[0] + 0x50) < 0x1E1U) && ((s16)D_1F800034[3] >= -0x14) && ((s16)D_1F800034[1] < 0x105)) {
        for (part = 0; part < g_SpriteCellPartCounts[index]; part++) {
            off  = index * 2;
            prim = (POLY_FT4*)g_GfxPrimCursor;
            p    = prim;
            for (j = 0; j < 2; j++) {
                SetPolyFT4(p);
                SetShadeTex(p, 0);
                p->x2 = D_1F800034[0];
                p->y2 = D_1F800034[1];
                p->x3 = D_1F800034[2];
                p->y3 = D_1F800034[3];
                setUV0(p, g_SpriteCellLeftU[index], g_SpriteCellTopV[off + j]);
                p->u2 = g_SpriteCellLeftU[index];
                p->u1 = g_SpriteCellRightU[index];
                p->u3 = g_SpriteCellRightU[index];
                p->v1 = g_SpriteCellTopV[off + j];
                setRGB0(p, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
                p->v3    = g_SpriteCellBottomV[off + j];
                p->v2    = g_SpriteCellBottomV[off + j];
                p->clut  = (g_SpriteCellCluts[index] >> 4) | 0x78C0;
                p->tpage = 0x2B;
                if (GetGraphType() != 1) {
                    p->tpage = 0x1B;
                    if (GetGraphType() == 2) {
                        p->tpage = 0x2B;
                    }
                }
                GFX_AddPrim(order, sizeof(POLY_FT4));
                p++;
            }
            for (j = 0; j < 4; j++) {
                D_1F800014[j].vx = D_8017F7A8[index * 6 + part * 2 + (j >> 1)] + *(s32*)(D_1F800000);
                D_1F800014[j].vy = D_8017F814[index * 6 + part * 2 + (j >> 1)] + *(s32*)(D_1F800000 + 4);
            }
            RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (s32*)&prim[0].x0, (s32*)&prim[0].x1, (s32*)&prim[1].x0, (s32*)&prim[1].x1, &depth, &flag);
        }
    }
}
#else
INCLUDE_ASM(func_8015642C);
#endif
