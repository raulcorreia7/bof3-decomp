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

    panel_data = &g_WindowClut;
    Menu_DrawClutStrip(*panel_data);
    panel_data += 0x15;
    selection                 = &D_80148656;
    selection_index           = *selection;
    g_UIPanelTasks[19].active = 1;
    g_UIPanelTasks[19].pos.vx = g_UIPanelTasks[selection_index + 4].pos.vx;
    g_UIPanelTasks[19].pos.vy = g_UIPanelTasks[selection_index + 4].pos.vy;
    UI_MessageSetVariable(0U, 5U, g_CharSlot[g_PartyFieldOrder[selection_index]] * 0xA4 + panel_data);
    g_UIPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = 0x12;
    input                                                     = INPUT_REPEATED(g_PadStates[0].pressed, (PADLup | PADLdown));
    count                                                     = Party_CountOrder(PARTY_ORDER_FIELD);
    old_selection                                             = *selection;
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
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    pad_state   = &g_PadStates[0].pressed;
    pad_buttons = *pad_state;
    if (pad_buttons & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
        func_801D2AC8();
        g_UIPanelTasks[19].active = 0;
        D_80148654                = 8;
        D_80148651 += 1;
        /* FAKE: keep pad reload after state updates. */
        FAKE_BARRIER();
        pad_buttons = *pad_state;
    }
    if (pad_buttons & g_InputMasks[MENU_INPUT_CANCEL]) {
        s32 i;

        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
        i = 0;
        while (i < Party_CountOrder(PARTY_ORDER_FIELD)) {
            g_UIPanelTasks[i + 12].state = 1;
            i++;
        }
        g_UIPanelTasks[MENU_START_PANEL_DESCRIPTION].state = 1;
        g_UIPanelTasks[19].active                          = 0;
        D_80148654                                         = 8;
        D_80148651 += 2;
    }
}
