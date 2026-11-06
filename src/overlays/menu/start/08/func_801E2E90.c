#include "start_08.h"

/* The 0x7E-byte six-row panel table and the seven-byte attribute tail copied
 * out of the fixed tables at the top of this unit. */
typedef struct MenuPanelRows {
    u8 rows[6][0x15];
} MenuPanelRows;

ASSERT_SIZE(MenuPanelRows, 0x7E);

typedef struct PanelTail {
    u8 bytes[7];
} PanelTail;

/* 76.7%; first difference at the prologue: retail saves s5 (sel live across the three calls, frame 0xC0), ours uses frame 0xB8. */
#ifdef NON_MATCHING
NON_MATCHING void func_801E2E90(s32 x, s32 y, s32 row_index) {
    MenuPanelRows table;
    PanelTail     tail;
    u8*           row;
    LINE_F2*      line;
    s32           index;
    u8            icon;
    u8*           sel;

    table = *(MenuPanelRows*)&D_801D0E28;
    tail  = *(PanelTail*)&D_801D0EA8;
    sel   = &g_WindowStyle;
    index = row_index & BYTE_MASK;
    row   = table.rows[index];

    UI_DrawWindow(x & HALF_MASK, y & HALF_MASK, 84, 16, 0, sel[0]);
    icon = *row;
    row++;
    UI_DrawText((s16)((x + 32) - icon * 4), (s16)(y + 1), 0, 6U, row);
    if (index != 1) {
        Resource_GetText((index + 0xCA));
    } else if (sel[4] == 0) {
        Resource_GetText((index + 0xCA) & HALF_MASK);
    } else {
        Resource_GetText(0xD0);
    }

    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    line->x0 = (s16)(x + 63);
    line->x1 = (s16)(x + 63);
    line->y0 = (s16)(y + 1);
    line->y1 = (s16)(y + 14);
    setRGB0(line, 128, 128, 128);
    GFX_AddPrim(1U, 0x10U);
}
#else
INCLUDE_ASM(func_801E2E90);
#endif
