#include "start_08.h"

MATCH void func_801D40D8(void) {
    s32 sel;
    /* FAKE: the merged pad read stays in v1; the best pure form (s32 local) puts it in s0 (2 rows). */
    FAKE_REG(u16, pressed, "v1");
    u8*  step;
    u8*  slot;
    u8** records;
    u16* pad;
    /* FAKE: retail keeps the toggle in s1; the best pure form (no pins) scores 16 rows. */
    FAKE_REG(s8*, toggle, "s1");

    Menu_DrawClutStrip(g_WindowClut);
    slot = &D_80148624;
    UI_MessageSetVariable(0, 0xC, Item_GetRecord(D_8014850E, g_ItemCategoryIds[D_8014850E][D_80148510]));
    D_801484CC                                     = 0x1A;
    toggle                                         = (s8*)&D_8014865B;
    *slot                                          = 1;
    sel                                            = 1 - *toggle;
    g_UIPanelTasks[MENU_START_PANEL_CURSOR].pos.vx = LOHU(D_801484C0) + (sel << 5) + 0xDE;
    g_UIPanelTasks[MENU_START_PANEL_CURSOR].pos.vy = LOHU(D_801484C2) + 5;
    records                                        = g_ItemCategoryIds;
    pad                                            = &g_PadStates[0].pressed;
    if (*pad & (PADLright | PADLleft)) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        *toggle ^= 1;
    }
    slot -= 0x120;
    pressed = *pad;
    if (pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (*toggle != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
            g_ItemCategoryIds[D_8014850E][D_80148510]    = 0;
            g_ItemCategoryCounts[D_8014850E][D_80148510] = 0;
        } else {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        }
        step = &D_80148651;
        *step -= 3;
        slot[0xD] = 0xFF;
        return;
    }
    if (pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        D_80148504.drawn_cursor = 0xFF;
        D_80148651 -= 3;
    }
}
