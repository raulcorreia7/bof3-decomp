#include "engine/slus/slus.h"

/* draws the shadowed sprite pairs of the field object at obj, positioned from the (x, y) map cell: projects a
 * three-vertex rim to cull off-screen objects, then emits two textured quadrangles per part from the
 * D_8017F* tables, the second projection filling the first corners of both. */
#ifdef NON_MATCHING
NON_MATCHING void func_8015642C(u8* obj, s32 x, s32 y) {
    s32       depth;
    s32       flag;
    s32       order;
    s32       index;
    s32       tpage;
    u8        shade;
    u8        value;
    s32       part;
    s32       j;
    s32       z;
    s16*      screen;
    POLY_FT4* prim;
    POLY_FT4* p;
    u8*       top;
    u8*       bottom;

    if ((*(u32*)obj >> 28) != 0) {
        order = 6;
    } else {
        order = g_AreaDrawMode;
    }
    index                             = (FIELD(u8, obj, 3u) & 0xF) - 1;
    *(s32*)(g_ScratchPad.cells.bytes) = (x - 0x81) << 7;
    g_ScratchPad.cells.words[1]       = (y - 0x80) << 7;
    z                                 = (s16) - ((s16)Area_HeightSample((x - 1) << 0x10, y << 0x10) / 2);
    screen                            = D_1F800034;
    g_ScratchPad.cells.words[2]       = z;
    g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx = *(s32*)(g_ScratchPad.cells.bytes);
    g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy = g_ScratchPad.cells.words[1];
    g_ScratchPadVectors[1].vz = g_ScratchPadVectors[3].vz = z;
    g_ScratchPadVectors[0].vz = g_ScratchPadVectors[2].vz = z - D_8017F880[index];
    RotTransPers3(&g_ScratchPadVectors[2], &g_ScratchPadVectors[3], &g_ScratchPadVectors[0], (s32*)screen, (s32*)(screen + 2), (s32*)(screen + 4), &depth, &flag);
    if (((u16)(screen[0] + 0x50) < 0x1E1U) && (D_1F800034[3] >= -0x14) && (D_1F800034[1] < 0x105)) {
        for (part = 0; part < g_SpriteCellPartCounts[index]; part++) {
            j      = 0;
            bottom = &((u8*)g_SpriteCellBottomV)[index * 2];
            prim   = (POLY_FT4*)g_GfxPrimCursor;
            top    = &((u8*)g_SpriteCellTopV)[index * 2];
            for (; j < 2; j++) {
                p = &prim[j];
                SetPolyFT4(p);
                SetShadeTex(p, 0);
                p->x2 = D_1F800034[0];
                p->y2 = D_1F800034[1];
                p->x3 = D_1F800034[2];
                p->y3 = D_1F800034[3];
                value = ((u8*)g_SpriteCellLeftU)[index];
                p->u0 = p->u2 = value;
                value         = ((u8*)g_SpriteCellRightU)[index];
                p->u1 = p->u3 = value;
                value         = *top;
                p->v0 = p->v1 = value;
                shade         = *bottom;
                value         = GFX_COLOR_NEUTRAL;
                setRGB0(p, value, value, value);
                p->v2 = p->v3 = shade;
                p->clut       = (((u8*)g_SpriteCellCluts)[index] >> 4) | 0x78C0;
                tpage         = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 704, 256);
                p->tpage      = tpage;
                GFX_AddPrim((u8)order, sizeof(POLY_FT4));
                bottom++;
                top++;
            }
            for (j = 0; j < 4; j++) {
                g_ScratchPadVectors[j].vx = ((u16(*)[6])D_8017F7A8)[index][part * 2 + (j >> 1)] + *(s32*)(g_ScratchPad.cells.bytes);
                g_ScratchPadVectors[j].vy = ((u16(*)[6])D_8017F814)[index][part * 2 + (j >> 1)] + g_ScratchPad.cells.words[1];
            }
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (s32*)&prim[0].x0, (s32*)&prim[0].x1, (s32*)&prim[1].x0,
                          (s32*)&prim[1].x1, &depth, &flag);
        }
    }
}
#else
INCLUDE_ASM(func_8015642C);
#endif
