#include "area016_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F4768(void) {
    Actor*    frame;
    POLY_FT4* primitive;
    POLY_FT4* source;
    SVECTOR*  quad;
    SVECTOR*  q1;
    SVECTOR*  q2;
    SVECTOR*  q3;
    long      depth;
    long      flag;
    s32       width;
    s32       row;
    s32       col;
    s32       offset;
    s32       x_low;
    s32       y_low;
    s32       x_high;
    s32       y_high;
    s32       uv;
    s32       tpage;

    frame = g_Task;
    if (frame->flags_02 == 0) {
        COORD_INT(frame->y) += (g_FrameCount & 0xF);
        frame->flags_02 = (u8)(frame->flags_02 + 1);
    }

    if ((g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) == 0) {
        return;
    }

    frame = g_Task;
    width = frame->unk_0B - 2;
    frame->y.fixed += 0x800 + (width << 10);
    if ((D_80104001 + 8) < COORD_INT(frame->y)) {
        COORD_INT(frame->y) = -8;
    }

    frame = g_Task;
    if ((abs(D_8014930A - COORD_INT(frame->x)) < 0x1A) || (abs(D_8014930E - COORD_INT(frame->y)) < 0x1A)) {
        primitive = (POLY_FT4*)g_GfxPrimCursor;
        row       = 0;
        SetPolyFT4(primitive);
        SetShadeTex(primitive, 0);

        quad     = D_1F800014;
        q1       = quad + 1;
        q2       = quad + 2;
        q3       = quad + 3;
        quad->vz = -0x300;
        q1->vz   = -0x300;
        q2->vz   = -0x300;
        q3->vz   = -0x300;

        frame  = g_Task;
        offset = (2 - width) << 8;
        offset += abs(0xF - (g_FrameCount & 0x1F));
        x_high = (frame->x.fixed >> 9) - 0x3FC0;
        y_high = ((s32)frame->y.fixed >> 9) - 0x3FC0;
        x_low  = x_high - offset;
        y_low  = y_high - offset;
        x_high += offset;
        y_high += offset;
        quad->vx = x_low;
        quad->vy = y_low;
        q1->vx   = x_high;
        q1->vy   = y_low;
        q2->vx   = x_low;
        q2->vy   = y_high;
        q3->vx   = x_high;
        q3->vy   = y_high;

        RotTransPers4(quad, q1, q2, q3, (long*)((u8*)primitive + 8), (long*)((u8*)primitive + 0x10),
                      (long*)((u8*)primitive + 0x18), (long*)((u8*)primitive + 0x20), &depth, &flag);

        func_80155560((u32)width | 0xBB509100u, primitive, 1);
        GFX_AddPrim(4, 0x28);

        for (row = 0; row < (2 - width) * 4 + 1; row++) {
            for (col = 0; col < (2 - width) * 4; col++) {
                frame = g_Task;
                source =
                    Area_FindCellQuad(COORD_INT(frame->x) - 2 + width + col, COORD_INT(frame->y) - 2 + width + row);
                if (source != NULL) {
                    primitive = (POLY_FT4*)g_GfxPrimCursor;
                    SetPolyFT4(primitive);
                    SetShadeTex(primitive, 0);
                    SetSemiTrans(primitive, 1);

                    LOWU(primitive->x0) = *(const u32*)&source->x0;
                    LOWU(primitive->x1) = *(const u32*)&source->x1;
                    LOWU(primitive->x2) = *(const u32*)&source->x2;
                    primitive->clut     = 0x78CB;
                    LOWU(primitive->x3) = *(const u32*)&source->x3;

                    tpage            = getTPage(0, 2, 704, 256);
                    primitive->tpage = (u16)tpage;
                    setRGB0(primitive, 0x28, 0x28, 0x28);

                    primitive->u0 = (u8)(D_801F51D8[width] + col * D_801F51E0[width]);
                    uv            = D_801F51E0[width] * COORD_FRAC(g_Task->y);
                    if (uv < 0) {
                        uv += 0xFFFF;
                    }
                    primitive->v0 = (u8)((D_801F51DC[width] + row * D_801F51E0[width]) - (uv >> 16));

                    primitive->u1 = (u8)(D_801F51E0[width] + (D_801F51D8[width] + col * D_801F51E0[width]));
                    uv            = D_801F51E0[width] * COORD_FRAC(g_Task->y);
                    if (uv < 0) {
                        uv += 0xFFFF;
                    }
                    primitive->v1 = (u8)((D_801F51DC[width] + row * D_801F51E0[width]) - (uv >> 16));

                    primitive->u2 = (u8)(D_801F51D8[width] + col * D_801F51E0[width]);
                    uv            = (D_801F51E0[width] & BYTE_MASK) * COORD_FRAC(g_Task->y);
                    if (uv < 0) {
                        uv += 0xFFFF;
                    }
                    primitive->v2 =
                        (u8)(D_801F51E0[width] + ((D_801F51DC[width] + row * D_801F51E0[width]) - (uv >> 16)));

                    primitive->u3 = (u8)(D_801F51E0[width] + (D_801F51D8[width] + col * D_801F51E0[width]));
                    uv            = (D_801F51E0[width] & BYTE_MASK) * COORD_FRAC(g_Task->y);
                    if (uv < 0) {
                        uv += 0xFFFF;
                    }
                    primitive->v3 =
                        (u8)(D_801F51E0[width] + ((D_801F51DC[width] + row * D_801F51E0[width]) - (uv >> 16)));

                    frame = g_Task;
                    Area_AddCellPrim((COORD_INT(frame->x) - 2 + width + col) << 16,
                                     (COORD_INT(frame->y) - 2 + width + row) << 16, 1, 0x28);
                }
            }
        }
    }
}
#else
/* blocker: register allocation; first diff: lui a1 against t0. */
INCLUDE_ASM(func_801F4768);
#endif
