#include "boss034_16.h"
#include "gfx/prim.h"

MATCH void func_800C23D4(s32 angle) {
    SVECTOR   vec;
    VECTOR    out;
    MATRIX    matrix;
    long      flag;
    POLY_FT4* poly;
    s32       lift;

    GFX_AddDrawMode(GetTPage(2, 0, 832, 256));

    PushMatrix();
    lift   = 40;
    vec.vx = 0;
    vec.vy = 0;
    vec.vz = (u16)angle * 16;
    RotMatrixYXZ(&vec, &matrix);
    SetRotMatrix(&matrix);

    out.vx = 0;
    out.vy = 0;
    out.vz = 0;
    TransMatrix(&matrix, &out);
    SetTransMatrix(&matrix);

    poly        = (POLY_FT4*)g_GfxPrimCursor;
    poly->tpage = GetTPage(2, 0, 832, 256);
    setRGB0(poly, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);

    vec.vx = -(g_Task->unk_0C / 2);
    vec.vy = -(g_Task->unk_10 / 2);
    RotTrans(&vec, &out, &flag);
    poly->x0 = g_Task->unk_18 + out.vx;
    poly->y0 = g_Task->unk_1C + (out.vy - lift);

    vec.vx = g_Task->unk_0C / 2;
    vec.vy = -(g_Task->unk_10 / 2);
    RotTrans(&vec, &out, &flag);
    poly->x1 = g_Task->unk_18 + out.vx;
    poly->y1 = g_Task->unk_1C + (out.vy - lift);

    vec.vx = -(g_Task->unk_0C / 2);
    vec.vy = g_Task->unk_10 / 2;
    RotTrans(&vec, &out, &flag);
    poly->x2 = g_Task->unk_18 + out.vx;
    poly->y2 = g_Task->unk_1C + (out.vy - lift);

    vec.vx = g_Task->unk_0C / 2;
    vec.vy = g_Task->unk_10 / 2;
    RotTrans(&vec, &out, &flag);
    poly->x3 = g_Task->unk_18 + out.vx;
    poly->y3 = g_Task->unk_1C + (out.vy - lift);

    setUV4(poly, 0, 0, 191, 0, 0, 104, 191, 104);
    SetPolyFT4(poly);
    GFX_AddPrim(1, sizeof(POLY_FT4));
    PopMatrix();
}
