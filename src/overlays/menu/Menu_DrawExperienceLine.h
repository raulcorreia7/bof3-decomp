/* Draws the experience progress line of a character from x, y: its x extent is the exp between the current
 * and next level scaled over the level-growth span, red, one semi-transparent line primitive. One definition
 * shared by the Bate, Shisu and shop overlays; each includes this file where the function sits. Every change
 * here must verify every member. */
/* func_801D4730 (bate), func_801D56D8 (shisu), func_801DA1D8 (shop) */
MATCH void Menu_DrawExperienceLine(u16 x, u16 y, u8 kind, u8 level, u32 exp) {
    LINE_F2* line;
    s16      x0;
    s32      first;
    s32      second;

    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    SetSemiTrans(line, 0);
    x0       = x;
    line->x0 = x0;
    line->y0 = y;
    first    = Char_GetExpForLevel(kind, level);
    second   = Char_GetExpForLevel(kind, (u8)(level + 1));
    if (second != first) {
        line->x1 = x + (exp - first) * 57 / (second - first);
    } else {
        line->x1 = x0;
    }
    line->y1 = y;
    line->r0 = 0x80;
    line->g0 = 0;
    line->b0 = 0;
    GFX_AddPrim(1, 0x10);
}
