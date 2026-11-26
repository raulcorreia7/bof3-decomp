#include "start_08.h"

MATCH void func_801D8188(void) {
    u8* slot = &g_UiPanelTasks[21].active;
    /* FAKE: branch-select byte pinned to s0; gcc swaps s0/s1 without it (94.78%). */
    FAKE_REG(s8*, toggle, "s0");
    u16* key;
    u8*  count;
    s16  bar;
    s32  sel;

    Menu_DrawClutStrip(g_WindowClut);
    /* FAKE: hides slot's constant so the bar read stays s1-relative; pure form 87.93%. */
    FAKE_OPAQUE(slot);
    bar                                                       = *(u16*)(slot - 0x164);
    *slot                                                     = 1;
    g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = 0x31;
    toggle                                                    = &D_8014865B;
    sel                                                       = 1 - *toggle;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].pos.vx            = bar + (sel << 5) + 0xDE;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].pos.vy            = g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].pos.vy + 5;
    key                                                       = &g_PadStates[0].pressed;
    slot -= 180;
    if (*key & (PADLright | PADLleft)) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        *toggle ^= 1;
    }
    if (*key & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (*toggle != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
            Char_AbilityAdd(*(Party_GetAbilities(g_UiPanelTasks[16].unk_0A, g_UiPanelTasks[16].unk_0B, CHAR_INDEX_RYU) + g_UiPanelTasks[16].unk_0C), CHAR_INDEX_RYU, 1, 0);
            *(Party_GetAbilities(g_UiPanelTasks[16].unk_0A, g_UiPanelTasks[16].unk_0B, 0) + g_UiPanelTasks[16].unk_0C) = 0;
        } else {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        }
        count = &D_80148651;
        *count -= 2;
        slot[0xD] = 0xFF;
        return;
    }
    if (*key & g_InputMasks[MENU_INPUT_CANCEL]) {
        g_UiPanelTasks[16].flags = 0xFF;
        D_80148651 -= 2;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
    }
}
