#include "start_08.h"

/* Start-overlay state bytes and the prompt bank this unit walks. */
extern u8 D_801ED105;

extern void Menu_DrawPortrait(u16 overlay_x, u16 overlay_y, u8 sprite_id, u8 shade);

MATCH void func_801E6388(s32 overlay_x, s32 overlay_y) {
    s32 base_x = overlay_x;
    s32 base_y = overlay_y;

    UI_DrawWindow((base_x + 3) & HALF_MASK, (base_y + 3) & HALF_MASK, 125, 47, 0, g_SaveData.window_style);
    Menu_DrawPortrait((base_x + 6) & HALF_MASK, (base_y + 2) & HALF_MASK, 0U, 0U);
    UI_DrawText((base_x + 59), (base_y + 25), (D_801ED105 != 0) * 2, 5U, s_CampMenuState);
    func_801AE214((s16)(base_x + ((u32)D_801ED7DC * 8 + 0x3B)), (s16)(base_y + 0x25), 8, 0);
    base_x <<= 0x10;
    base_y <<= 0x10;
    UI_DrawSpriteRun(base_x >> 0x10, base_y >> 0x10, &D_801ECFB8, 0);
}
