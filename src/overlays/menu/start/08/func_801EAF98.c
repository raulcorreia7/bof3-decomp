#include "start_08.h"

/* Draws the inventory panel of the character menu: its item list from the
 * D_80145548 flag word, the title, the corner and edge frame sprites. */
#ifdef NON_MATCHING
NON_MATCHING void func_801EAF98(MenuPanelTask* task) {
    u8   scroll_y;
    u8   scroll_rows;
    u8   first;
    u8   i;
    u8   count;
    s32  y;
    s32  title_x;
    u8*  title;
    u32* flags;

    flags = &D_80145548;
    count = 0;
    for (i = 0; i < 0x12; i++) {
        if (*flags & (1 << i)) {
            D_801ED878[count++] = i + 1;
        }
    }
    while (count < 0x12) {
        D_801ED878[count] = 0;
        count++;
    }
    UI_WindowDraw((task->pos.x + 3) & HALF_MASK, (task->pos.y + 3) & HALF_MASK, MENU_INVENTORY_WINDOW_WIDTH, MENU_INVENTORY_WINDOW_HEIGHT, 0, g_WindowStyle);
    first = UI_ScrollList(&task->unk_0A, &scroll_y, &scroll_rows, &task->unk_08);
    y     = (s8)scroll_y + (task->pos.y + 0x1A);
    for (i = first; i < first + (scroll_rows + 9); i++) {
        if (D_801ED878[i] == 0) {
            break;
        }
        if (task->unk_0B == i) {
            UI_IconDraw((task->pos.x + 7) & HALF_MASK, (y + 2) & HALF_MASK, 6, 1);
            UI_TextDraw((s16)(task->pos.x + 17), (s16)y, UI_TEXT_DIM, TEXT_LENGTH_MAX, UI_MessageGetText(D_801ED878[i] + 0x4171));
            y -= 2;
        }
        UI_IconDraw((task->pos.x + 7) & HALF_MASK, (y + 2) & HALF_MASK, 6, 0);
        UI_TextDraw((s16)(task->pos.x + 17), (s16)y, 0, TEXT_LENGTH_MAX, UI_MessageGetText(D_801ED878[i] + 0x4171));
        if (task->unk_0B == i) {
            y += 2;
        }
        y += 0xD;
    }
    task->unk_0C = D_801ED878[task->unk_0B];
    UI_WindowDraw((task->pos.x + 3) & HALF_MASK, (task->pos.y + 3) & HALF_MASK, MENU_INVENTORY_WINDOW_WIDTH, MENU_INVENTORY_TOP_HEIGHT, 0, g_WindowStyle);
    UI_WindowDraw((task->pos.x + 3) & HALF_MASK, (task->pos.y + 146) & HALF_MASK, MENU_INVENTORY_WINDOW_WIDTH, MENU_INVENTORY_BOTTOM_HEIGHT, 0, g_WindowStyle);
    title   = (u8*)&D_801ED608;
    title_x = (Game_ReadCommand(title) & BYTE_MASK) * 4 - 78;
    UI_TextDraw((s16)(task->pos.x - title_x), (s16)(task->pos.y + 7), 0, MENU_LABEL_LENGTH, title);
    UI_SpriteDrawRun((s16)task->pos.x, (s16)task->pos.y, (u8*)&D_801ED5F0, UI_SPRITE_ALT_PAGE);
    UI_SpriteDrawRun((s16)task->pos.x, (s16)task->pos.y, (u8*)&D_801ED5FC, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < 0xA; i++) {
        UI_SpriteDraw((s16)(task->pos.x + (i + 5) * 8), (s16)task->pos.y, 1, UI_SPRITE_ALT_PAGE);
    }
    for (i = 0; i < 0xF; i++) {
        UI_SpriteDraw((s16)task->pos.x, (s16)(task->pos.y + (i + 3) * 8), 4, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw((s16)(task->pos.x + 144), (s16)(task->pos.y + 24), 0x16, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < 0xC; i++) {
        UI_SpriteDraw((s16)(task->pos.x + 144), (s16)(task->pos.y + (i + 5) * 8), 0x17, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw((s16)(task->pos.x + 144), (s16)(task->pos.y + 136), 0x18, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw((s16)task->pos.x, (s16)(task->pos.y + 144), 0x19, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < 0x11; i++) {
        UI_SpriteDraw((s16)(task->pos.x + (i + 1) * 8), (s16)(task->pos.y + 144), 0x1A, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw((s16)(task->pos.x + 8), (s16)task->pos.y, 0x32, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw((s16)(task->pos.x + 144), (s16)task->pos.y, 0x33, UI_SPRITE_ALT_PAGE);
    UI_ListDrawScrollbar(D_801ED878, task->unk_0A, (s16)(task->pos.x + 0x90), (s16)(task->pos.y + 0x18), 9, 0x12, 0x74);
}
#else
INCLUDE_ASM(func_801EAF98);
#endif
