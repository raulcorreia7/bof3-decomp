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
    s32  entry_index;
    /* FAKE: pin shared fourth argument in a3. */
    FAKE_REG(s32, selection, "a3");
    func_800B06F4(g_UIPanelCurrent->pos.vx, g_UIPanelCurrent->pos.vy, g_UIPanelCurrent->unk_08, g_UIPanelCurrent->unk_09);

    style = &g_WindowStyle;
    UI_WindowDraw((u16)(g_UIPanelCurrent->pos.vx + 6u), (u16)(g_UIPanelCurrent->pos.vy + 33u), (u16)(g_UIPanelCurrent->unk_08 * 8u - 15u), (u16)(g_UIPanelCurrent->unk_09 * 8u - 39u), 0, *style);

    UI_WindowDraw((u16)(g_UIPanelCurrent->pos.vx + 54u), (u16)(g_UIPanelCurrent->pos.vy + 6u), 72, 24, 0, *style);

    UI_WindowDraw((u16)(g_UIPanelCurrent->pos.vx + 135u), (u16)(g_UIPanelCurrent->pos.vy + 10u), 48, 16, 0, *style);

    panel_count = -(BATTLE_ACTIVE_MEMBER->chr.ap < D_801463B8[0]) & 0x7;
    UI_TextDrawAscii((u16)(g_UIPanelCurrent->pos.vx + 136u), (u16)(g_UIPanelCurrent->pos.vy + 12u), panel_count, (const void*)(D_800B6D1C));

    TEXT_Format(g_UITextFormatBuffer, D_80096A04, D_801463B8[0]);

    UI_TextDrawAscii((u16)(g_UIPanelCurrent->pos.vx + 160u), (u16)(g_UIPanelCurrent->pos.vy + 12u), panel_count, (const void*)(g_UITextFormatBuffer));

    if (SEL_MODE == 4) {
        sel_substate = SEL_SUBSTATE;
        selection    = sel_substate;
        if (sel_substate == -1) {
            ((void (*)(u16, u16, s32, s32))UI_CursorDraw)((g_UIPanelCurrent->pos.vx + 14), (g_UIPanelCurrent->pos.vy + 12), 0, selection);
        } else {
            ((void (*)(u16, u16, s32, s32))UI_CursorDraw)(((u16)(g_UIPanelCurrent->pos.vx + 14) + SEL_SLOT * 30), ((u16)(g_UIPanelCurrent->pos.vy + 44) + ((entry_index = selection & BYTE_MASK) << 5)),
                                                          0, selection);
        }
    }
}
