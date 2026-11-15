#include "area111_13.h"

/* Redraws the 7x7 grid of cell codes, restores the packed cell map and queues
 * the cursor rectangles the front-side gate selects. */
MATCH void func_801F46A8(void) {
    s16 col;
    s16 row;

    if (D_80143F03 == 0) {
        SYS_ClearFlag(g_SceneEventFlags, 0x28);
    }
    if (D_80143F03 == 1) {
        for (col = 0; col < 7; col++) {
            for (row = 0; row < 7; row++) {
                func_801F4604(row, col, D_801F5BC8[col][row]);
            }
        }
        for (row = 0; row < 7; row++) {
            AREA111_CELL_MAP_WORD(row) = D_801F5BFC[row];
        }
        if (SYS_TestFlag(g_SceneEventFlags, 0x28) == 0) {
            func_801A4BC0(0x11, 0xAD, 0x50);
            func_801A4BC0(0x12, 0xAD, 0x50);
            func_801A4BC0(0x11, 0xAE, 0x00);
            func_801A4BC0(0x12, 0xAE, 0x00);
        } else {
            func_801A4BC0(0x11, 0xAD, 0xA1);
            func_801A4BC0(0x12, 0xAD, 0xA1);
            func_801A4BC0(0x11, 0xAE, 0xC0);
            func_801A4BC0(0x12, 0xAE, 0xC0);
        }
    }
    if (D_80143F03 == 5) {
        func_801A4BC0(0x0A, 0x08, 0x50);
        func_801A4BC0(0x0B, 0x08, 0x50);
    }
}
