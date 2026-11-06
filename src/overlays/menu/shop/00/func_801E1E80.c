#include "shop_00.h"

MATCH void func_801E1E80(s16 panel_x, s16 panel_y) {
    s16 x;
    s16 y;
    s16 base_x;
    s16 base_y;
    s32 scaled_y;
    s32 value;
    u8  i;

    x      = panel_x;
    y      = panel_y;
    base_x = x;
    base_y = y;

    scaled_y = y << 16;
    UI_DrawWindow(x + 3, y + 3, 85, 16, 0, D_80144952);
    y += 4;
    UI_DrawText(x + 4, y, 0, 0xFF, D_801E5D38);
    value = Item_Count(ITEM_CAT_ITEM, ITEM_SKILL_INK, 0);
    sprintf((char*)g_UiFormatBuffer, D_801D0E84, value & HALF_MASK);
    UI_DrawAsciiString(x + 52, y, 0, g_UiFormatBuffer);
    UI_DrawSpriteRun(x, (scaled_y >> 16), D_801E5CC0, 0);
    for (i = 0; i < 9; i++) {
        UI_DrawSpriteRun((base_x + (i * 8)), (scaled_y >> 16), D_801E5CCC, 0);
    }
    UI_DrawSpriteRun(base_x, base_y, D_801E5CD8, 0);
}
