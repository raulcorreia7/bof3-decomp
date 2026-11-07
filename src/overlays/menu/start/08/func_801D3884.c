#include "start_08.h"

MATCH void func_801D3884(void) {
    s32 trigger;
    s8  step_down;
    u8  step_up;
    u8* state;
    u8* counter;

    Menu_DrawClutStrip(D_80144953);
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].unk_10 = 0x17;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].active      = 1;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.x       = (u16)g_MenuPanelTasks[MENU_START_PANEL_ITEMS].pos.x + 0x2A;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.y       = (u16)g_MenuPanelTasks[MENU_START_PANEL_ITEMS].pos.y + 7;
    trigger = INPUT_REPEATED(g_InputPressed, (INPUT_DIRECTIONAL | PADL1 | PADR1));
    g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C = 0xFF;
    if (trigger & PADLleft) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
        g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_10 = 0x32;
        step_down                                       = g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A - 1;
        g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A = step_down;
        if (step_down < 0) {
            g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A = 3;
        }
        /* Both directions store the stepped entry. */
        goto store_selection;
    }
    if (trigger & PADLright) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
        g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_10 = 0x31;
        step_up                                         = g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A + 1;
        g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A = step_up;
        if ((u32)(step_up & BYTE_MASK) >= 4U) {
            g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A = 0;
        }
    store_selection:
        /* Shared tail of both step directions. */
        g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B =
            s_ChoiceMenuValues[g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A];
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_PlayCue(EMI_CUE_ID(1, 3));
        g_MenuPanelTasks[14].handler = 6;
        g_MenuPanelTasks[14].mode    = 0xF;
        g_MenuPanelTasks[14].active  = 1;
        g_MenuPanelTasks[14].pos.x   = 0xB4;
        g_MenuPanelTasks[14].pos.y   = 0x3C;
        g_MenuPanelTasks[14].unk_0B  = 0;
        g_MenuPanelTasks[14].unk_0C  = 0xFF;
        state                        = &D_80148652;
        /* FAKE: scheduler hoists the state load past the stores. */
        MATCH_BARRIER();
        g_MenuPanelTasks[14].unk_0A = g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A;
        *state += 1;
        return;
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        counter = &D_80148651;
        *counter -= 3;
    }
}
