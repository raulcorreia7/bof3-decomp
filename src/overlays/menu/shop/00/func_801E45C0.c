#include "shop_00.h"

#ifdef NON_MATCHING
/* Draws the message panel: the packed entry rows with their cursor shading and
 * class icon, then the tab strips and the scrollbar. */
NON_MATCHING void func_801E45C0(MenuPanelTask* task) {
    u8  entries[17];
    u8  row_offset;
    u8  count;
    u8  i;
    u8  packed;
    u8  first;
    u8  current;
    u8  shade;
    s32 start;
    s32 row_y;
    s32 title_x;
    s32 enabled;

    packed  = 0;
    first   = 0x7F;
    current = 0x7F;
    for (i = 0; i < 0x11; i++) {
        if (((D_8014554F[i >> 3] >> (i & 7)) & 1) != 0) {
            if (task->unk_0B == packed) {
                first       = packed;
                task->flags = i;
            }
            if (task->unk_0C == packed) {
                current = packed;
            }
            entries[packed] = i + 1;
            packed++;
        }
    }
    for (i = packed; i < 0x11; i++) {
        entries[i] = 0;
    }
    if (first == 0x7F) {
        task->flags = 0xFF;
    }

    UI_WindowDraw((task->pos.x + 3) & HALF_MASK, (task->pos.y + 3) & HALF_MASK, 0x71, 0x9A, 0, g_WindowStyle);

    start = UI_ScrollList(&task->unk_0A, &row_offset, &count, &task->unk_08);
    row_y = (s8)row_offset + (task->pos.y + 0x1A);
    for (i = start; (u8)i < (u8)start + count + 9; i++) {
        if (entries[i] != 0) {
            enabled = func_801E4C2C((entries[i] - 1) & BYTE_MASK);
            if (first == i) {
                UI_TextDraw((s16)(task->pos.x + 0x13), (s16)row_y, UI_TEXT_DIM, TEXT_LENGTH_MAX, UI_MessageGetText(entries[i] + 0x110));
                if ((enabled & BYTE_MASK) == 0) {
                    UI_IconDraw((task->pos.x + 8) & HALF_MASK, (row_y + 2) & HALF_MASK, 6, 1);
                } else {
                    UI_TextDraw((s16)(task->pos.x + 8), (s16)row_y, UI_TEXT_DIM, TEXT_LENGTH_MAX, (u8*)&D_801E5F68);
                }
                row_y -= 2;
            }
            shade = (current == i) * 2;
            UI_TextDraw((s16)(task->pos.x + 0x13), (s16)row_y, shade, TEXT_LENGTH_MAX, UI_MessageGetText(entries[i] + 0x110));
            if ((enabled & BYTE_MASK) == 0) {
                UI_IconDraw((task->pos.x + 8) & HALF_MASK, (row_y + 2) & HALF_MASK, 6, 0);
            } else {
                UI_TextDraw((s16)(task->pos.x + 8), (s16)row_y, shade, TEXT_LENGTH_MAX, (u8*)&D_801E5F68);
            }
            if (first == i) {
                row_y += 2;
            }
        }
        row_y += 0xD;
    }

    UI_WindowDraw((task->pos.x + 3) & HALF_MASK, (task->pos.y + 3) & HALF_MASK, 0x71, 0x14, 0, g_WindowStyle);
    UI_WindowDraw((task->pos.x + 3) & HALF_MASK, (task->pos.y + 0x92) & HALF_MASK, 0x71, 8, 0, g_WindowStyle);

    title_x = (Game_ReadCommand((u8*)D_801E5F60) & BYTE_MASK) * 4 - 0x3A;
    UI_TextDraw((s16)(task->pos.x - title_x), (s16)(task->pos.y + 7), 0, MENU_LABEL_LENGTH, (u8*)D_801E5F60);

    UI_SpriteDrawRun((s16)task->pos.x, (s16)task->pos.y, (u8*)D_801E5F48, UI_SPRITE_ALT_PAGE);
    UI_SpriteDrawRun((s16)task->pos.x, (s16)task->pos.y, (u8*)D_801E5F54, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < 5; i++) {
        UI_SpriteDraw((s16)(task->pos.x + (i + 5) * 8), (s16)task->pos.y, 1, UI_SPRITE_ALT_PAGE);
    }
    for (i = 0; i < 15; i++) {
        UI_SpriteDraw((s16)task->pos.x, (s16)(task->pos.y + (i + 3) * 8), 4, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw((s16)(task->pos.x + 0x68), (s16)(task->pos.y + 0x18), 0x16, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < 12; i++) {
        UI_SpriteDraw((s16)(task->pos.x + 0x68), (s16)(task->pos.y + (i + 5) * 8), 0x17, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw((s16)(task->pos.x + 0x68), (s16)(task->pos.y + 0x88), 0x18, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw((s16)task->pos.x, (s16)(task->pos.y + 0x90), 0x19, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < 12; i++) {
        UI_SpriteDraw((s16)(task->pos.x + (i + 1) * 8), (s16)(task->pos.y + 0x90), 0x1A, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw((s16)(task->pos.x + 8), (s16)task->pos.y, 0x32, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw((s16)(task->pos.x + 0x68), (s16)task->pos.y, 0x33, UI_SPRITE_ALT_PAGE);
    UI_ListDrawScrollbar(entries, task->unk_0A, (s16)(task->pos.x + 0x68), (s16)(task->pos.y + 0x18), 9, 0x11, 0x74);
}
#else
INCLUDE_ASM(func_801E45C0);
#endif
