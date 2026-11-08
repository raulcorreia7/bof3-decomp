#include "start_08.h"

MATCH void func_801DD6D0(s16 x, s16 y, u8 kind, u8 level, u32 exp) {
    LINE_F2* line;
    s16      x0;
    s32      first;
    s32      second;

    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    SetSemiTrans(line, 0);
    x0 = x;
    setXY0(line, x0, y);
    first  = Char_GetExpForLevel(kind, level);
    second = Char_GetExpForLevel(kind, (u8)(level + 1));
    if (second != first) {
        line->x1 = x + (exp - first) * 57 / (second - first);
    } else {
        line->x1 = x0;
    }
    line->y1 = y;
    setRGB0(line, 128, 0, 0);
    GFX_AddPrim(1, sizeof(LINE_F2));
}
