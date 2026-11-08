#include "start_08.h"

extern s8 D_80148656; /* local: s8 read; a sibling copy is u8 */

MATCH void func_801D24AC(void) {
    u8 count;

    Message_SetVariable(0, 5, g_Characters[g_CharSlot[g_PartyFieldOrder[D_80148656]]].name);
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = 0x12;
    Menu_DrawClutStrip(D_80144953);
    count      = D_80148654;
    D_80148654 = count + 0xFF;
    if (count == 0) {
        D_80148651 += 1;
    }
}
