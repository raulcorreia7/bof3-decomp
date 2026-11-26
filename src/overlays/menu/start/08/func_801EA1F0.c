#include "start_08.h"

MATCH void func_801EA1F0(MenuPanelTask* task) {
    u8  group_index;
    s16 row;
    u8  i;
    u32 color;
    UI_WindowDraw((task->pos.vx + 3) & HALF_MASK, (task->pos.vy + 3) & HALF_MASK, 101, (D_801ED560[task->unk_0A][0] * 16) + 25, 0, g_WindowStyle);
    UI_TextDraw((task->pos.vx + 39), (task->pos.vy + 7), 0, TEXT_LENGTH_MAX, (u8*)D_801ED534[0]);
    UI_SpriteDrawRun(task->pos.vx, task->pos.vy, D_801ED468, UI_SPRITE_ALT_PAGE);
    group_index = task->unk_0A;
    i           = 0;
    if (D_801ED560[group_index][0] != 0) {
        do {
            color = D_801ED534[D_801ED560[group_index][i + 1]];
            if (i == task->unk_0C) {
                row = i * 0x10 + 0x1A;
                UI_TextDraw((task->pos.vx + 7), (task->pos.vy + row), UI_TEXT_DIM, TEXT_LENGTH_MAX, (u8*)color);
                UI_TextDraw((task->pos.vx + 7), (task->pos.vy + row - 2), UI_TEXT_HIGHLIGHT, TEXT_LENGTH_MAX, (u8*)color);
            } else if (i == task->unk_0B) {
                row = i * 0x10 + 0x1A;
                UI_TextDraw((task->pos.vx + 7), (task->pos.vy + row), UI_TEXT_DIM, TEXT_LENGTH_MAX, (u8*)color);
                UI_TextDraw((task->pos.vx + 7), (task->pos.vy + row - 2), 0, TEXT_LENGTH_MAX, (u8*)color);
            } else {
                row = i * 0x10 + 0x1A;
                UI_TextDraw((task->pos.vx + 7), (task->pos.vy + row), 0, TEXT_LENGTH_MAX, (u8*)color);
            }
            UI_SpriteDrawRun(task->pos.vx, (task->pos.vy + (i * 2 + 3) * 8), D_801ED48C, UI_SPRITE_ALT_PAGE);
            UI_SpriteDrawRun(task->pos.vx, (task->pos.vy + (i * 2 + 4) * 8), D_801ED48C, UI_SPRITE_ALT_PAGE);
            group_index = task->unk_0A;
            i++;
        } while (i < D_801ED560[group_index][0]);
    }
    row = i * 0x10 + 0x18;
    UI_SpriteDrawRun(task->pos.vx, (task->pos.vy + row), D_801ED498, UI_SPRITE_ALT_PAGE);
}
