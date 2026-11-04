#include "sisyou_00.h"

/* func_801D1C44: u8 preserves the retail call sequence. */
s32 Char_GetExpForLevel(s32 char_id, u8 level);

/* Line primitive setup helper (SetLineF2 in the PsyQ libgpu object). */

/* Returns character `char_id`'s cumulative experience at `level`: the sum of
 * the `exp` halfwords of the first `level` 8-byte LevelGrowth rows for that
 * character in the level-growth table (0x318-byte character stride); -1 when
 * `level` is 100 or more. */

MATCH void Menu_DrawExperienceLine(u16 x, u16 y, u8 char_id, u8 level, u32 exp) {
    LINE_F2* line;
    s16      x0;
    s32      level_exp;
    s32      next_exp;

    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    SetSemiTrans(line, 0);
    x0        = x;
    line->x0  = x0;
    line->y0  = y;
    level_exp = Char_GetExpForLevel(char_id, level);
    next_exp  = Char_GetExpForLevel(char_id, level + 1);
    if (next_exp != level_exp) {
        line->x1 = x + (exp - level_exp) * 57 / (next_exp - level_exp);
    } else {
        line->x1 = x0;
    }
    line->y1 = y;
    setRGB0(line, 128, 0, 0);
    GFX_AddPrim(1, 0x10);
}
