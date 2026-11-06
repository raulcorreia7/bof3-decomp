#include "battle_15.h"

/* The panel sprite steps this many pixels along each edge. */
#define BATTLE_PANEL_STEP      8
/* The panel texture page. */
#define BATTLE_PANEL_TEXTURE_Y 0x100
#define BATTLE_PANEL_TEXTURE_X 0x340

MATCH void func_800B06F4(s16 x, s16 y, u8 width, u8 height) {
    s16 px;
    u8  i;
    u8  j;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0,
                GetTPage(0, 0, BATTLE_PANEL_TEXTURE_X, BATTLE_PANEL_TEXTURE_Y) & HALF_MASK, NULL);
    GFX_AddPrim(1, 0xC);

    for (i = 1; i < height - 1; i++) {
        for (j = 1; j < width - 1; j++) {
            UI_DrawSprite(x + j * BATTLE_PANEL_STEP, y + i * BATTLE_PANEL_STEP, 0x25, 1);
        }
    }
    for (i = 2; i < width - 2; i++) {
        px = x + i * BATTLE_PANEL_STEP;
        UI_DrawSprite(px, y, 0x24, 1);
        UI_DrawSprite(px, y + (height - 1) * BATTLE_PANEL_STEP, 0x28, 1);
    }
    for (i = 2; i < height - 2; i++) {
        px = y + i * BATTLE_PANEL_STEP;
        UI_DrawSprite(x, px, 0x2A, 1);
        UI_DrawSprite(x + (width - 1) * BATTLE_PANEL_STEP, px, 0x2B, 1);
    }
    UI_DrawSprite(x, y, 0x23, 1);
    px = x + (width - 2) * BATTLE_PANEL_STEP;
    UI_DrawSprite(px, y, 0x26, 1);
    UI_DrawSprite(x, y + (height - 2) * BATTLE_PANEL_STEP, 0x27, 1);
    UI_DrawSprite(px, y + (height - 2) * BATTLE_PANEL_STEP, 0x29, 1);
}
