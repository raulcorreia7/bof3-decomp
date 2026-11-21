#include "start_08.h"

/* Start-overlay state bytes and the prompt bank this unit walks. */

MATCH void func_801E6388(s32 overlay_x, s32 overlay_y) {
    s32 base_x = overlay_x;
    s32 base_y = overlay_y;

    UI_WindowDraw((base_x + 3) & HALF_MASK, (base_y + 3) & HALF_MASK, 125, 47, 0, g_WindowStyle);
    Menu_DrawPortrait((base_x + 6) & HALF_MASK, (base_y + 2) & HALF_MASK, 0U, 0U);
    UI_TextDraw((base_x + 59), (base_y + 25), (D_801ED105 != 0) * 2, CHARACTER_NAME_LENGTH, s_CampMenuState);
    UI_CursorDrawName((s16)(base_x + ((u32)D_801ED7DC * 8 + 0x3B)), (s16)(base_y + 0x25), 8, 0);
    base_x <<= 0x10;
    base_y <<= 0x10;
    UI_SpriteDrawRun(base_x >> 0x10, base_y >> 0x10, &D_801ECFB8, 0);
}
