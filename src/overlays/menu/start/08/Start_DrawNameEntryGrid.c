#include "start_08.h"

/* Character grid of the name entry window: page `page` of D_801ECDBC holds 8 rows of 12 cells. The cells in column 10
 * of rows 3 to 7 hold a command id 1 to 5, drawn as a label; column 11 of those rows is part of that label. The
 * cursor sits at (D_801ED7E0, D_801ED7E4). */
#ifdef NON_MATCHING
NON_MATCHING void Start_DrawNameEntryGrid(u8 page, s32 grid_x, s32 grid_y) {
    /* 87.1%; regalloc: retail moves grid_y to v0 before the label copy, ours keeps it in a2. */
    NameEntryLabels labels;
    u16             base_y;
    s16             x;
    s16             y;
    u16             row;
    u16             col;
    u8*             cell;
    u16             cursor_x;

    base_y = grid_y;
    y      = base_y + 6;
    row    = 0;
    labels = D_801D0F00;
    UI_DrawWindow(grid_x & HALF_MASK, base_y, 272, 123, 0, g_WindowStyle);
    cell = D_801ECDBC + (page & BYTE_MASK) * 0x60;
    for (; row < 8; row++) {
        x = grid_x + 4;
        for (col = 0; col < 12; col++) {
            if (col == 10 && row >= 3) {
                switch (*cell) {
                    case 1:
                        UI_DrawText(x, y, 4, 5, labels.next);
                        break;
                    case 2:
                        UI_DrawText(x, y, 4, 5, labels.back);
                        break;
                    case 3:
                        UI_DrawText(x, y, 2, 5, labels.quit);
                        break;
                    case 4:
                        UI_DrawText(x, y, 2, 5, labels.start);
                        break;
                }
            } else if (col != 11 || row < 3) {
                UI_DrawText(x, y, 0, 1, cell);
            }
            x += (col == 4 || col == 9) ? 0x1C : 0x14;
            cell++;
        }
        y += 0xE;
    }
    x = grid_x + 6 + D_801ED7E0 * 0x14;
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
INCLUDE_ASM(Start_DrawNameEntryGrid);
#endif
