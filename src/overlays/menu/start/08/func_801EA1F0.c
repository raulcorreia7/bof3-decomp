#include "start_08.h"

MATCH void func_801EA1F0(MenuPanelTask* task) {
    u8  group_index;
    s16 row;
    u8  i;
    u32 color;
    UI_DrawWindow((task->pos.x + 3) & HALF_MASK, (task->pos.y + 3) & HALF_MASK, 101, (D_801ED560[task->unk_0A][0] * 16) + 25, 0, g_WindowStyle);
    UI_DrawText((task->pos.x + 39), (task->pos.y + 7), 0, 255U, (u8*)D_801ED534[0]);
    UI_DrawSpriteRun(task->pos.x, task->pos.y, D_801ED468, 1);
    group_index = task->unk_0A;
    i           = 0;
    if (D_801ED560[group_index][0] != 0) {
        do {
            color = D_801ED534[D_801ED560[group_index][i + 1]];
            if (i == task->unk_0C) {
                row = i * 0x10 + 0x1A;
                UI_DrawText((task->pos.x + 7), (task->pos.y + row), 7, 255U, (u8*)color);
                UI_DrawText((task->pos.x + 7), (task->pos.y + row - 2), 2, 255U, (u8*)color);
            } else if (i == task->unk_0B) {
                row = i * 0x10 + 0x1A;
                UI_DrawText((task->pos.x + 7), (task->pos.y + row), 7, 255U, (u8*)color);
                UI_DrawText((task->pos.x + 7), (task->pos.y + row - 2), 0, 255U, (u8*)color);
            } else {
                row = i * 0x10 + 0x1A;
                UI_DrawText((task->pos.x + 7), (task->pos.y + row), 0, 255U, (u8*)color);
            }
            UI_DrawSpriteRun(task->pos.x, (task->pos.y + (i * 2 + 3) * 8), D_801ED48C, 1);
            UI_DrawSpriteRun(task->pos.x, (task->pos.y + (i * 2 + 4) * 8), D_801ED48C, 1);
            group_index = task->unk_0A;
            i++;
        } while (i < D_801ED560[group_index][0]);
    }
    row = i * 0x10 + 0x18;
    UI_DrawSpriteRun(task->pos.x, (task->pos.y + row), D_801ED498, 1);
}
