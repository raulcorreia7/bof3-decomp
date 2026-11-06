#include "shop_00.h"

#define PANEL_X    FIELD(u16, arg0, 0x4u)
#define PANEL_Y    FIELD(u16, arg0, 0x6u)
#define PANEL_SEL  FIELD(u8, arg0, 0xAu)
#define PANEL_PREV FIELD(u8, arg0, 0xBu)

MATCH void func_801E3F5C(void* arg0) {
    u32 color;
    u8  i;
    u8* count;
    s16 row;

    count = &D_801E5F0C;

    UI_DrawWindow((PANEL_X + 3), (PANEL_Y + 3), 101, *count * 16 + 25, 0, g_SaveData.window_style);
    UI_DrawText((PANEL_X + 39), (PANEL_Y + 7), 0, 0xFF, (u8*)D_801E5EFC[0]);
    UI_DrawSpriteRun(PANEL_X, PANEL_Y, D_801E5E7C, 1);
    i = 0;
    if (*count != 0) {
        do {
            color = D_801E5EFC[D_801E5F0D[i]];
            if (i == PANEL_PREV) {
                row = i * 0x10 + 0x1A;
                UI_DrawText((PANEL_X + 7), (PANEL_Y + row), 7, 0xFF, (u8*)color);
                UI_DrawText((PANEL_X + 7), (PANEL_Y + row - 2), 2, 0xFF, (u8*)color);
            } else if (i == PANEL_SEL) {
                row = i * 0x10 + 0x1A;
                UI_DrawText((PANEL_X + 7), (PANEL_Y + row), 7, 0xFF, (u8*)color);
                UI_DrawText((PANEL_X + 7), (PANEL_Y + row - 2), 0, 0xFF, (u8*)color);
            } else {
                row = i * 0x10 + 0x1A;
                UI_DrawText((PANEL_X + 7), (PANEL_Y + row), 0, 0xFF, (u8*)color);
            }
            UI_DrawSpriteRun(PANEL_X, (PANEL_Y + (i * 2 + 3) * 8), D_801E5EA0, 1);
            UI_DrawSpriteRun(PANEL_X, (PANEL_Y + (i * 2 + 4) * 8), D_801E5EA0, 1);
            i++;
        } while (i < D_801E5F0C);
    }
    row = i * 0x10 + 0x18;
    UI_DrawSpriteRun(PANEL_X, (PANEL_Y + row), D_801E5EAC, 1);
}
