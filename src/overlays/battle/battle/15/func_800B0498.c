#include "battle_15.h"

/* Battle-panel state cells owned by the main executable. Declared as
 * arrays so their decayed addresses stay in registers across calls. */

/* Battle-selection cells. Read through plain byte views: each site reads
 * the cell exactly once, so the volatile qualification battle_15.h carries
 * is not needed and would block byte-load folding. */
#define SEL_MODE     (*MEM_PTR(u8, &g_BattleUiStep))
#define SEL_SUBSTATE (*MEM_PTR(s8, &g_BattlePanelEntry))
#define SEL_SLOT     (*MEM_PTR(u8, &D_801462E7))

MATCH void func_800B0498(void) {
    u8*  style;
    s32  sel_substate;
    s32  panel_count;
    s32  panel_home;
    s32* panel_sink = &panel_home;
    s32  substate_row;
    /* FAKE: pin shared fourth argument in a3. */
    MATCH_REG(s32, row, "a3");
    func_800B06F4((s16)g_MenuCurrentPanel->x, (s16)g_MenuCurrentPanel->y, g_MenuCurrentPanel->unk_08,
                  g_MenuCurrentPanel->unk_09);

    style = &D_80144952;
    UI_DrawWindow((s32)(u16)(g_MenuCurrentPanel->x + 6u), (s32)(u16)(g_MenuCurrentPanel->y + 33u),
                  (s32)(u16)((u16)g_MenuCurrentPanel->unk_08 * 8u - 15u),
                  (s32)(u16)((u16)g_MenuCurrentPanel->unk_09 * 8u - 39u), 0, (s32)*style);

    UI_DrawWindow((s32)(u16)(g_MenuCurrentPanel->x + 54u), (s32)(u16)(g_MenuCurrentPanel->y + 6u), 72, 24, 0,
                  (s32)*style);

    UI_DrawWindow((s32)(u16)(g_MenuCurrentPanel->x + 135u), (s32)(u16)(g_MenuCurrentPanel->y + 10u), 48, 16, 0,
                  (s32)*style);

    panel_count = -(s32)(BATTLE_ACTIVE_ROW->stats.current_ap < D_801463B8[0]) & 7;
    UI_DrawAsciiString((s16)(u16)(g_MenuCurrentPanel->x + 136u), (s16)(u16)(g_MenuCurrentPanel->y + 12u), panel_count,
                       (const void*)(D_800B6D1C));

    sprintf((char*)g_UiFormatBuffer, (char*)D_80096A04, (s32)D_801463B8[0]);

    UI_DrawAsciiString((s16)(u16)(g_MenuCurrentPanel->x + 160u), (s16)(u16)(g_MenuCurrentPanel->y + 12u), panel_count,
                       (const void*)(g_UiFormatBuffer));

    if (SEL_MODE == 4) {
        sel_substate = (s32)SEL_SUBSTATE;
        row          = sel_substate;
        if (sel_substate == -1) {
            ((void (*)(u16, u16, s32, s32))Menu_DrawCursorSprite)((u16)(g_MenuCurrentPanel->x + 14),
                                                                  (u16)(g_MenuCurrentPanel->y + 12), 0, row);
        } else {
            ((void (*)(u16, u16, s32, s32))Menu_DrawCursorSprite)(
                (u16)((s32)(u16)(g_MenuCurrentPanel->x + 14) + SEL_SLOT * 30),
                (u16)((s32)(u16)(g_MenuCurrentPanel->y + 44) + ((substate_row = row & BYTE_MASK) << 5)), 0, row);
        }
    }
}
