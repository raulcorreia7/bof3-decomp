#include "shop_00.h"

/* nonmatching unmeasured: tried do-while(0) AID scope, a search over source rewrites: text_clut reused for the px copy (95.74), y/px/py
 * update orders. resume: py in s2 and the shaded byte in s3. */
/* func_801D826C */
#ifdef NON_MATCHING
NON_MATCHING void Menu_DrawCharacterWindow(s32 px, s32 py, u8 character_slot, s32 shaded, s32 unused) {
    Character* stats;
    u32        clut;
    u32        text_clut;
    s32        text_y;
    s32        x;
    s32        y;

    clut = (u8)shaded ? 7 : 0;
    UI_DrawWindow((px + 3) & HALF_MASK, (py + 3) & HALF_MASK, 125, 48, (u8)shaded, CHARACTER_BLOCK->window_style);
    x = px;
    /* AID: a do-while(0) scope steers the register homes of x, y and stats. */
    do {
        y = py;
        px += 0x56;
        py += 2;
        stats     = &g_Characters[character_slot];
        text_clut = px;
        Menu_DrawCharacterPortrait(text_clut & HALF_MASK, py & HALF_MASK, stats->character_id,
                                   (u8)shaded == 0 ? (stats->status >> 6) & 2 : 1);
        text_clut = clut & BYTE_MASK;
        UI_DrawText((s16)(x + 20), (s16)(y + 3), text_clut, 5, stats);
    } while (0);
    sprintf(g_UiFormatBuffer, g_MenuStatFormat, stats->level);
    text_y = (s16)(y + 0x17);
    UI_DrawGlyphString(x + 22, text_y, text_clut, g_UiFormatBuffer);
    if ((*(u32*)&stats->status & (STATUS_CONFUSED | STATUS_POISONED)) == (STATUS_CONFUSED | STATUS_POISONED)) {
        if (g_FrameCount & 0x20) {
            UI_DrawTextString(x + 46, text_y, text_clut != 0 ? text_clut : 1, 0x10, D_801E5814);
        } else {
            UI_DrawTextString(x + 46, text_y, text_clut != 0 ? text_clut : 1, 0x10, D_801E581C);
        }
    } else if (stats->status & STATUS_POISONED) {
        UI_DrawTextString(x + 46, text_y, text_clut != 0 ? text_clut : 1, 0x10, D_801E5814);
    } else if (stats->status & STATUS_CONFUSED) {
        UI_DrawTextString(x + 46, text_y, text_clut != 0 ? text_clut : 1, 0x10, D_801E581C);
    }
    if (stats->current_hp < (u32)(stats->max_hp >> 2)) {
        stats->status |= STATUS_LOW_HP;
    } else {
        stats->status &= ~STATUS_LOW_HP;
    }
    if ((u8)shaded == 0) {
        if (stats->status & STATUS_LOW_HP) {
            clut = 4;
        }
        if (stats->current_hp < 2) {
            clut = 2;
        }
    } else {
        clut = 7;
    }
    sprintf(g_UiFormatBuffer, D_801D0CE8, stats->current_hp);
    UI_DrawGlyphString(x + 22, y + 31, clut, g_UiFormatBuffer);
    if ((u8)shaded == 0) {
        clut = (stats->fatigue != 0) * 4;
    } else {
        clut = 7;
    }
    sprintf(g_UiFormatBuffer, D_801D0CF0, stats->max_hp);
    UI_DrawGlyphString(x + 22, y + 31, clut, g_UiFormatBuffer);
    clut = (u8)shaded ? 7 : 0;
    if ((u8)shaded == 0) {
        if (stats->current_ap < (u32)(stats->max_ap >> 2)) {
            clut = 4;
        }
        if (stats->current_ap == 0) {
            clut = 2;
        }
    } else {
        clut = 7;
    }
    sprintf(g_UiFormatBuffer, D_801D0CE8, stats->current_ap);
    UI_DrawGlyphString(x + 22, y + 39, clut, g_UiFormatBuffer);
    clut = (u8)shaded ? 7 : 0;
    sprintf(g_UiFormatBuffer, D_801D0CF0, stats->max_ap);
    UI_DrawGlyphString(x + 22, y + 39, clut, g_UiFormatBuffer);
    UI_DrawSpriteRun(x, y, D_801E547C, 0);
    Menu_DrawExperienceLine(x + 0x14, y + 0x12, character_slot, stats->level, stats->exp);
}
#else
/* Same body in the shop, start, Bate and Shisu overlays; the shop draft is the closest start, and the retail register homes keep py in s2 and the shaded byte in s3. */
INCLUDE_ASM(Menu_DrawCharacterWindow);
#endif
