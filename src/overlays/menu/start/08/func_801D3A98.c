#include "start_08.h"

MATCH void func_801D3A98(void) {
    MenuPanelTask* task;
    s32            input;
    u8             entry;
    u8*            rows;

    Menu_DrawClutStrip(g_WindowClut);
    g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0C             = 0xFF;
    g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = 0x18;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].active            = 1;
    g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0C             = 0xFF;
    task                                                      = &g_UiPanelTasks[14];
    task->unk_0C                                              = 0xFF;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].pos.vx            = task->pos.vx + 5;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].pos.vy            = (u16)(task->pos.vy + (task->unk_0B * 16 + 26));

    input = INPUT_REPEATED(g_PadStates[0].pressed, (PADLup | PADLdown));
    if (input & PADLup) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        if ((s8)--task->unk_0B < 0) {
            task->unk_0B = D_801EC3E0[task->unk_0A * 6] - 1;
        }
    } else if (input & PADLdown) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        task->unk_0B++;
        if (D_801EC3E0[task->unk_0A * 6] - 1 < task->unk_0B) {
            task->unk_0B = 0;
        }
    }

    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        rows  = D_801EC3E0;
        entry = (rows + task->unk_0A * 6 + task->unk_0B)[1];
        if (entry != 0) {
            func_801D49F8(entry);
            return;
        }
        g_UiPanelTasks[MENU_START_PANEL_ITEMS].flags  = 0xFF;
        g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0C = s_ChoiceMenuCursors[g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A];
        /* g_MenuStep.state through g_MenuStep.sub_step: retail keeps the symbol-relative
         * address in a register for the read-modify-write. */
        (&g_MenuStep.sub_step)[1]++;
    } else if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        task->active = 0;
        (&g_MenuStep.sub_step)[1]--;
    }
}
