#include "boss034_16.h"
#include "gfx/prim.h"

MATCH void func_800C23D4(s32 angle) {
    SVECTOR   vec;
    VECTOR    out;
    MATRIX    matrix;
    long      flag;
    POLY_FT4* poly;
    s32       lift;

    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_15BIT, TPAGE_ABR_HALF, 832, 256));

    PushMatrix();
    lift = 40;
    setVector(&vec, 0, 0, (u16)angle * 16);
    RotMatrixYXZ(&vec, &matrix);
    SetRotMatrix(&matrix);

    setVector(&out, 0, 0, 0);
    TransMatrix(&matrix, &out);
    SetTransMatrix(&matrix);

    poly        = (POLY_FT4*)g_GfxPrimCursor;
    poly->tpage = GetTPage(TPAGE_DEPTH_15BIT, TPAGE_ABR_HALF, 832, 256);
    setRGB0(poly, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);

    vec.vx = -(SELF(PartyMember)->unk_0C / 2);
    vec.vy = -(SELF(PartyMember)->unk_10 / 2);
    RotTrans(&vec, &out, &flag);
    setXY0(poly, SELF(PartyMember)->unk_18 + out.vx, SELF(PartyMember)->unk_1C + (out.vy - lift));

    vec.vx = SELF(PartyMember)->unk_0C / 2;
    vec.vy = -(SELF(PartyMember)->unk_10 / 2);
    RotTrans(&vec, &out, &flag);
    poly->x1 = SELF(PartyMember)->unk_18 + out.vx;
    poly->y1 = SELF(PartyMember)->unk_1C + (out.vy - lift);

    vec.vx = -(SELF(PartyMember)->unk_0C / 2);
    vec.vy = SELF(PartyMember)->unk_10 / 2;
    RotTrans(&vec, &out, &flag);
    poly->x2 = SELF(PartyMember)->unk_18 + out.vx;
    poly->y2 = SELF(PartyMember)->unk_1C + (out.vy - lift);

    vec.vx = SELF(PartyMember)->unk_0C / 2;
    vec.vy = SELF(PartyMember)->unk_10 / 2;
    RotTrans(&vec, &out, &flag);
    poly->x3 = SELF(PartyMember)->unk_18 + out.vx;
    poly->y3 = SELF(PartyMember)->unk_1C + (out.vy - lift);

    setUV4(poly, 0, 0, 191, 0, 0, 104, 191, 104);
    SetPolyFT4(poly);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
    PopMatrix();
}
