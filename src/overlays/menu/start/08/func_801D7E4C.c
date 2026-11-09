#include "start_08.h"

MATCH void func_801D7E4C(void) {
    s32 buttons;
    u8  count;
    u8  old;
    u8  i;
    u8  state;
    u8* latch;
    u16 x;
    u16 y;
    u8* cursor;
    s8* sel;
    s8  result;

    u8* flag;
    Menu_DrawClutStrip(D_80144953);
    state = g_MenuPanelTasks[MENU_START_PANEL_ITEMS].state;
    flag  = &D_80148624;
    latch = flag - 0x48;
    *flag = 0;
    if (state == 0) {
        x                                                      = g_MenuPanelTasks[MENU_START_PANEL_ITEMS].pos.x;
        y                                                      = D_80148658[0] * 0x36;
        *latch                                                 = 1;
        g_MenuPanelTasks[MENU_START_PANEL_CURSOR_FRAME].unk_0B = 1;
        D_801485E0                                             = x;
        D_801485E2                                             = g_MenuPanelTasks[MENU_START_PANEL_ITEMS].pos.y + y;
    } else {
        *latch = 0;
    }
    buttons = INPUT_REPEATED(g_InputPressed, INPUT_DIRECTIONAL);
    count   = Party_CountOrder(PARTY_ORDER_FIELD);
    cursor  = D_80148658;
    old     = *cursor;
    if (buttons & PADLup) {
        *cursor -= 1;
        if ((s8)*cursor < 0) {
            *cursor = count - 1;
        }
    } else if (buttons & PADLdown) {
        *cursor += 1;
        if ((s8)*cursor > count - 1) {
            *cursor = 0;
        }
    }
    sel = (s8*)D_80148658;
    if ((s8)old != *sel) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
    }
    Message_SetVariable(0, 0xC,
                        (const u8*)&g_Abilities[Party_GetAbilities(
                            g_MenuPanelTasks[16].unk_0A, g_MenuPanelTasks[16].unk_0B, 0)[g_MenuPanelTasks[16].unk_0C]]);
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = 0x30;
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        /* D_8014857A stays its own symbol: a g_MenuPanelTasks[16] view shifts the base registers */
        result = func_801E7D20(
            g_CharSlot[g_PartyFieldOrder[D_8014857A]], g_CharSlot[g_PartyFieldOrder[*sel]],
            Party_GetAbilities(D_8014857A, g_MenuPanelTasks[16].unk_0B, 0)[g_MenuPanelTasks[16].unk_0C], 0);
        D_801ED654 = result;
        if (result == 1 || result == 5) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 9));
            return;
        }
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
        return;
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
        D_801485DC = 0;
        for (i = 0; i < Party_CountOrder(PARTY_ORDER_FIELD); i++) {
            g_MenuPanelTasks[i + 0xD].state = 9;
            g_MenuPanelTasks[i + 4].state   = 8;
        }
        g_BattleChoicePhase        = 3;
        g_MenuPanelTasks[16].flags = 0xFF;
        latch                      = &g_MenuStep.sub_step;
        (*latch)--;
    }
}
