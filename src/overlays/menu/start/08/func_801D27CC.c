#include "start_08.h"

extern s8 D_80148656;

MATCH void func_801D27CC(void) {
    u8* records;
    u8* panel_data;
    panel_data = &D_80144953;
    Menu_DrawClutStrip(*panel_data);
    records = panel_data + 0x15;
    Message_SetVariable(0, 5, g_CharSlot[g_PartyFieldOrder[D_80148656]] * 0xA4 + records);
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = 0x12;
    if (D_80148654 == 0) {
        if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
            SND_PlayCue(EMI_CUE_ID(1, 6));
            SND_PlayCue(EMI_CUE_ID(1, 2));
            func_801D2C7C();
            D_80148654 = 8;
            D_80148651 -= 2;
        }
    } else {
        D_80148654 -= 1;
    }
}
