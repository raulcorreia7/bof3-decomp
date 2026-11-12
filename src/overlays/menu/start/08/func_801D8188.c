#include "start_08.h"

MATCH void func_801D8188(void) {
    u8* slot = &D_80148624;
    /* FAKE: branch-select byte pinned to s0; gcc swaps s0/s1 without it (94.78%). */
    FAKE_REG(s8*, toggle, "s0");
    u16* key;
    u8*  count;
    s16  bar;
    s32  sel;

    Menu_DrawClutStrip(D_80144953);
    /* FAKE: hides slot's constant so the bar read stays s1-relative; pure form 87.93%. */
    FAKE_OPAQUE(slot);
    bar                                                         = *(u16*)(slot - 0x164);
    *slot                                                       = 1;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = 0x31;
    toggle                                                      = &D_8014865B;
    sel                                                         = 1 - *toggle;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.x             = bar + (sel << 5) + 0xDE;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.y             = g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].pos.y + 5;
    key                                                         = &g_InputPressed;
    slot -= 180;
    if (*key & (PADLright | PADLleft)) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        *toggle ^= 1;
    }
    if (*key & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (*toggle != 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
            Char_AddAbility(*(Party_GetAbilities(g_MenuPanelTasks[16].unk_0A, g_MenuPanelTasks[16].unk_0B, CHAR_INDEX_RYU) + g_MenuPanelTasks[16].unk_0C), 0, 1, 0);
            *(Party_GetAbilities(g_MenuPanelTasks[16].unk_0A, g_MenuPanelTasks[16].unk_0B, 0) + g_MenuPanelTasks[16].unk_0C) = 0;
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        }
        count = &D_80148651;
        *count -= 2;
        slot[0xD] = 0xFF;
        return;
    }
    if (*key & g_InputMasks[MENU_INPUT_CANCEL]) {
        g_MenuPanelTasks[16].flags = 0xFF;
        D_80148651 -= 2;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
    }
}
