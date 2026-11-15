#include "shop_00.h"

MATCH void func_801E3F5C(void* panel) {
    MenuPanelTask* record;
    u32            color;
    u8             i;
    u8*            count;
    s16            row;

    record = panel;
    count  = &D_801E5F0C;

    UI_DrawWindow((record->pos.x + 3), (record->pos.y + 3), 101, *count * 16 + 25, 0, g_WindowStyle);
    UI_DrawText((record->pos.x + 39), (record->pos.y + 7), 0, TEXT_LENGTH_MAX, (u8*)D_801E5EFC[0]);
    UI_DrawSpriteRun(record->pos.x, record->pos.y, D_801E5E7C, 1);
    i = 0;
    if (*count != 0) {
        do {
            color = D_801E5EFC[D_801E5F0D[i]];
            if (i == record->unk_0B) {
                row = i * 0x10 + 0x1A;
                UI_DrawText((record->pos.x + 7), (record->pos.y + row), 7, TEXT_LENGTH_MAX, (u8*)color);
                UI_DrawText((record->pos.x + 7), (record->pos.y + row - 2), 2, TEXT_LENGTH_MAX, (u8*)color);
            } else if (i == record->unk_0A) {
                row = i * 0x10 + 0x1A;
                UI_DrawText((record->pos.x + 7), (record->pos.y + row), 7, TEXT_LENGTH_MAX, (u8*)color);
                UI_DrawText((record->pos.x + 7), (record->pos.y + row - 2), 0, TEXT_LENGTH_MAX, (u8*)color);
            } else {
                row = i * 0x10 + 0x1A;
                UI_DrawText((record->pos.x + 7), (record->pos.y + row), 0, TEXT_LENGTH_MAX, (u8*)color);
            }
            UI_DrawSpriteRun(record->pos.x, (record->pos.y + (i * 2 + 3) * 8), D_801E5EA0, 1);
            UI_DrawSpriteRun(record->pos.x, (record->pos.y + (i * 2 + 4) * 8), D_801E5EA0, 1);
            i++;
        } while (i < D_801E5F0C);
    }
    row = i * 0x10 + 0x18;
    UI_DrawSpriteRun(record->pos.x, (record->pos.y + row), D_801E5EAC, 1);
}
