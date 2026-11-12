#include "battle_15.h"

/* Battle-panel state cells owned by the main executable. Declared as
 * arrays so their decayed addresses stay in registers across calls. */

/* Battle-selection cells. Read through plain byte views: each site reads
 * the cell exactly once, so the volatile qualification battle_15.h carries
 * is not needed and would block byte-load folding. */
#define SEL_MODE     (*MEM_PTR(u8, &g_Battle.ui_step))
#define SEL_SUBSTATE (*MEM_PTR(s8, &g_Battle.cursor.panel_entry))
#define SEL_SLOT     (*MEM_PTR(u8, &D_801462E7))

MATCH void func_800B0498(void) {
    u8*  style;
    s32  sel_substate;
    s32  panel_count;
    s32  panel_home;
    s32* panel_sink = &panel_home;
    s32  substate_row;
    /* FAKE: pin shared fourth argument in a3. */
    FAKE_REG(s32, row, "a3");
    func_800B06F4(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, g_MenuCurrentPanel->unk_08, g_MenuCurrentPanel->unk_09);

    style = &g_WindowStyle;
    UI_DrawWindow((u16)(g_MenuCurrentPanel->pos.x + 6u), (u16)(g_MenuCurrentPanel->pos.y + 33u), (u16)(g_MenuCurrentPanel->unk_08 * 8u - 15u), (u16)(g_MenuCurrentPanel->unk_09 * 8u - 39u), 0, *style);

    UI_DrawWindow((u16)(g_MenuCurrentPanel->pos.x + 54u), (u16)(g_MenuCurrentPanel->pos.y + 6u), 72, 24, 0, *style);

    UI_DrawWindow((u16)(g_MenuCurrentPanel->pos.x + 135u), (u16)(g_MenuCurrentPanel->pos.y + 10u), 48, 16, 0, *style);

    panel_count = -(BATTLE_ACTIVE_ROW->chr.ap < D_801463B8[0]) & 0x7;
    UI_DrawAsciiString((u16)(g_MenuCurrentPanel->pos.x + 136u), (u16)(g_MenuCurrentPanel->pos.y + 12u), panel_count, (const void*)(D_800B6D1C));

    TEXT_Format(g_UiFormatBuffer, D_80096A04, D_801463B8[0]);

    UI_DrawAsciiString((u16)(g_MenuCurrentPanel->pos.x + 160u), (u16)(g_MenuCurrentPanel->pos.y + 12u), panel_count, (const void*)(g_UiFormatBuffer));

    if (SEL_MODE == 4) {
        sel_substate = SEL_SUBSTATE;
        row          = sel_substate;
        if (sel_substate == -1) {
            ((void (*)(u16, u16, s32, s32))Menu_DrawCursorSprite)((g_MenuCurrentPanel->pos.x + 14), (g_MenuCurrentPanel->pos.y + 12), 0, row);
        } else {
            ((void (*)(u16, u16, s32, s32))Menu_DrawCursorSprite)(((u16)(g_MenuCurrentPanel->pos.x + 14) + SEL_SLOT * 30),
                                                                  ((u16)(g_MenuCurrentPanel->pos.y + 44) + ((substate_row = row & BYTE_MASK) << 5)), 0, row);
        }
    }
}
