#include "start_08.h"

MATCH void func_801D3884(void) {
    s32 trigger;
    s8  step_down;
    u8  step_up;
    u8* state;
    u8* counter;

    Menu_DrawClutStrip(g_WindowClut);
    g_UIPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = 0x17;
    g_UIPanelTasks[MENU_START_PANEL_CURSOR].active            = 1;
    g_UIPanelTasks[MENU_START_PANEL_CURSOR].pos.vx            = (u16)g_UIPanelTasks[MENU_START_PANEL_ITEMS].pos.vx + 0x2A;
    g_UIPanelTasks[MENU_START_PANEL_CURSOR].pos.vy            = (u16)g_UIPanelTasks[MENU_START_PANEL_ITEMS].pos.vy + 7;
    trigger                                                   = INPUT_REPEATED(g_PadStates[0].pressed, (INPUT_DIRECTIONAL | PADL1 | PADR1));
    g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0C             = 0xFF;
    if (trigger & PADLleft) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        g_UIPanelTasks[MENU_START_PANEL_ITEMS].u.list.tabs = 0x32;
        step_down                                          = g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0A - 1;
        g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0A      = step_down;
        if (step_down < 0) {
            g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0A = 3;
        }
        /* Both directions store the stepped entry. */
        goto store_selection;
    }
    if (trigger & PADLright) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        g_UIPanelTasks[MENU_START_PANEL_ITEMS].u.list.tabs = 0x31;
        step_up                                            = g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0A + 1;
        g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0A      = step_up;
        if ((u32)(step_up & BYTE_MASK) >= 4U) {
            g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0A = 0;
        }
    store_selection:
        /* Shared tail of both step directions. */
        g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0B = s_ChoiceMenuValues[g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0A];
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        g_UIPanelTasks[14].panel  = 6;
        g_UIPanelTasks[14].mode   = 0xF;
        g_UIPanelTasks[14].active = 1;
        g_UIPanelTasks[14].pos.vx = 180;
        g_UIPanelTasks[14].pos.vy = 60;
        g_UIPanelTasks[14].unk_0B = 0;
        g_UIPanelTasks[14].unk_0C = 0xFF;
        state                     = &g_MenuStep.state;
        /* FAKE: scheduler hoists the state load past the stores. */
        FAKE_BARRIER();
        g_UIPanelTasks[14].unk_0A = g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0A;
        *state += 1;
        return;
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        counter = &g_MenuStep.sub_step;
        *counter -= 3;
    }
}
