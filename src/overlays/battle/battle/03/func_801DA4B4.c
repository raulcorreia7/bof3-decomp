#include "battle_03.h"

MATCH void func_801DA4B4(s16 x0, s16 y0, s16 x1, s16 y1, u8 r, u8 g, u8 b) {
    BattleSpritePrimitive* primitive;

    GFX_AddDrawMode(GetTPage(0, 0, 960, 0));
    primitive = (BattleSpritePrimitive*)g_GfxPrimCursor;
    SetLineF2((LINE_F2*)primitive);
    setRGB0(primitive, r, g, b);
    primitive->x0     = x0;
    primitive->y0     = y0;
    primitive->unk_0C = x1;
    primitive->unk_0E = y1;
    PSX_SET_SEMI_TRANSPARENT(primitive);
    GFX_AddPrim(1, 0x10);
}
