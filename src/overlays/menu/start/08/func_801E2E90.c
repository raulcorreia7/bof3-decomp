#include "start_08.h"

/* The 0x7E-byte six-row panel table and the seven-byte attribute tail copied
 * out of the fixed tables at the top of this unit. */
typedef struct MenuPanelRows {
    u8 rows[6][0x15];
} MenuPanelRows;

ASSERT_SIZE(MenuPanelRows, 0x7E);

typedef struct MenuPanelTail {
    u8 bytes[7];
} MenuPanelTail;

#ifdef NON_MATCHING
NON_MATCHING void func_801E2E90(s32 x, s32 y, s32 row_index) {
    MenuPanelRows table;
    MenuPanelTail tail;
    u8*           row;
    LINE_F2*      line;
    s32           index;
    u8            icon;
    s32           text_left;
    /* The integer round trip keeps the window base in one register, as retail does. */
    u8*           window_style = (u8*)(u32)&g_WindowStyle;

    table     = *(MenuPanelRows*)&D_801D0E28;
    /* Retail copies the unused attribute tail and sizes its frame with it. */
    tail      = *(MenuPanelTail*)&D_801D0EA8;
    index     = row_index & BYTE_MASK;
    row       = table.rows[index];
    text_left = x + 32;

    UI_WindowDraw(x, y, 84, 16, 0, *window_style);
    icon = *row;
    row++;
    UI_TextDraw(text_left - icon * 4, y + 1, 0, 6, row);
    if (index != 1) {
        UI_MessageGetText((u8)row_index + 0xCA);
    } else {
        UI_MessageGetText((u16)(window_style[4] == 0 ? (u8)row_index + 0xCA : 0xD0));
    }

    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    line->x1 = x + 63;
    setXY0(line, x + 63, y + 1);
    line->y1 = y + 14;
    setRGB0(line, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(LINE_F2));
}
#else
INCLUDE_ASM(func_801E2E90);
#endif
