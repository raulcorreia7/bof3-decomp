#include "start_08.h"

/* Character grid of the name entry window: page `page` of D_801ECDBC holds 8 rows of 12 cells. The cells in column 10
 * of rows 3 to 7 hold a command id 1 to 5, drawn as a label; column 11 of those rows is part of that label. The
 * cursor sits at (D_801ED7E0, D_801ED7E4). */
#ifdef NON_MATCHING
NON_MATCHING void Menu_DrawNameEntryGrid(u8 page, s32 grid_x, s32 grid_y) {
    /* Near match: same 189 instructions and frame; retail's prologue saves and parameter copies are
     * ordered s0 pair, s7 pair, ours s7 pair, grid_y copy, s0 pair (scheduler tie). */
    NameEntryLabels labels;
    u16             base_y;
    s16             x;
    s16             y;
    u16             row;
    u16             col;
    u8*             cell;
    u16             cursor_x;

    memcpy(&labels, &D_801D0F00, sizeof(labels));
    base_y = grid_y;
    UI_DrawWindow(grid_x & HALF_MASK, base_y, 272, 123, 0, g_WindowStyle);
    cell = D_801ECDBC + (page & BYTE_MASK) * 0x60;
    y    = base_y + 6;
    for (row = 0; row < 8; row++) {
        x = grid_x + 4;
        for (col = 0; col < 12; col++) {
            if (col == 10 && row >= 3) {
                switch (*cell) {
                    case NAME_ENTRY_NEXT:
                        UI_DrawText(x, y, 4, 5, labels.next);
                        break;
                    case NAME_ENTRY_BACK:
                        UI_DrawText(x, y, 4, 5, labels.back);
                        break;
                    case NAME_ENTRY_QUIT:
                        UI_DrawText(x, y, 2, 5, labels.quit);
                        break;
                    case NAME_ENTRY_START:
                        UI_DrawText(x, y, 2, 5, labels.start);
                        break;
                }
            } else if (col != 11 || row < 3) {
                UI_DrawText(x, y, 0, 1, cell);
            }
            if (col == 4 || col == 9) {
                x += 0x1C;
            } else {
                x += 0x14;
            }
            cell++;
        }
        y += 0xE;
    }
    x = (s16)(grid_x + 6) + D_801ED7E0 * 0x14;
    y = base_y + 8 + D_801ED7E4 * 0xE;
    if (D_801ED7E0 >= 5) {
        x += 8;
    }
    if (D_801ED7E0 >= 10) {
        x += 8;
    }
    if (D_801ED7E0 == 11 && D_801ED7E4 >= 3) {
        x -= 0x14;
    }
    cursor_x = x;
    Menu_DrawCursorSprite(cursor_x, y & HALF_MASK, 0);
}
#else
INCLUDE_ASM(Menu_DrawNameEntryGrid);
#endif
