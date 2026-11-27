#include "start_08.h"

extern s8 D_80148656;

MATCH void func_801D27CC(void) {
    u8* records;
    u8* panel_data;
    panel_data = &g_WindowClut;
    Menu_DrawClutStrip(*panel_data);
    records = panel_data + 0x15;
    UI_MessageSetVariable(0, 5, g_CharSlot[g_PartyFieldOrder[D_80148656]] * 0xA4 + records);
    g_UIPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = 0x12;
    if (D_80148654 == 0) {
        if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
            func_801D2C7C();
            D_80148654 = 8;
            D_80148651 -= 2;
        }
    } else {
        D_80148654 -= 1;
    }
}
