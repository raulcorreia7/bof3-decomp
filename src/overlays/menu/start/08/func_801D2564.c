#include "start_08.h"

extern s8 D_80148656; /* local: s8 read; a sibling copy is u8 */

MATCH void func_801D2564(void) {
    s32  selection_index;
    u8*  panel_data;
    s8*  selection;
    s32  input;
    u8   count;
    u8   old_selection;
    s8   new_selection;
    u16* pad_state;
    u16  pad_buttons;

    panel_data = &D_80144953;
    Menu_DrawClutStrip(*panel_data);
    panel_data += 0x15;
    selection       = &D_80148656;
    selection_index = *selection;
    /* FAKE: preserve flag store after selection read. */
    ORDER_LOCK(D_801485DC = 1);
    D_801485E0 = g_MenuPanelTasks[selection_index + 4].pos.x;
    /* FAKE: preserve first table store order. */
    MATCH_FAKE_BARRIER();
    D_801485E2 = g_MenuPanelTasks[selection_index + 4].pos.y;
    TEXT_SetVariable(0U, 5U, g_CharSlot[g_PartyFieldOrder[selection_index]] * 0xA4 + panel_data);
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].unk_10 = 0x12;
    input                                                 = INPUT_REPEATED(g_InputPressed, (PADLup | PADLdown));
    count                                                 = Party_CountOrder(PARTY_ORDER_FIELD);
    old_selection                                         = *selection;
    if ((input & PADLup) != 0) {
        new_selection = old_selection - 1;
        *selection    = new_selection;
        if (new_selection < 0) {
            *selection = count - 1;
        }
    } else if ((input & PADLdown) != 0) {
        new_selection = old_selection + 1;
        *selection    = new_selection;
        if (new_selection >= count) {
            *selection = 0;
        }
    }
    if (old_selection != D_80148656) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
    }
    pad_state   = &g_InputPressed;
    pad_buttons = *pad_state;
    if (pad_buttons & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_PlayCue(EMI_CUE_ID(1, 3));
        SND_PlayCue(EMI_CUE_ID(1, 2));
        func_801D2AC8();
        D_801485DC = 0;
        D_80148654 = 8;
        D_80148651 += 1;
        /* FAKE: keep pad reload after state updates. */
        MATCH_FAKE_BARRIER();
        pad_buttons = *pad_state;
    }
    if (pad_buttons & g_InputMasks[MENU_INPUT_CANCEL]) {
        s32 i;

        SND_PlayCue(EMI_CUE_ID(1, 6));
        SND_PlayCue(EMI_CUE_ID(1, 2));
        i = 0;
        while (i < Party_CountOrder(PARTY_ORDER_FIELD)) {
            g_MenuPanelTasks[i + 12].state = 1;
            i++;
        }
        g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].state = 1;
        D_801485DC                                           = 0;
        D_80148654                                           = 8;
        D_80148651 += 2;
    }
}
