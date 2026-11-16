#include "start_08.h"

extern s8 D_80148656;

/* Handles the start menu command list. */
MATCH void func_801D8680(void) {
    s16*           panel;
    MenuPanelTask* task;
    u8*            rows;
    s32            buttons;
    u8             at_end;
    u8             entry;
    u8             flag_value;
    u8             next_count;
    s32            row_index;

    Menu_DrawClutStrip(D_80144953);
    /* FAKE: pure C reaches 92.0% after the panel, table, mask, and counter rewrites. */
    FAKE_HOLD(flag_value, 0xFF);
    panel  = &D_801484CC;
    *panel = 0x18;
    FAKE_USE(flag_value);
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].active = 1;
    task                                             = (MenuPanelTask*)&panel[0x76];
    g_MenuPanelTasks[18].unk_0C                      = flag_value;
    g_MenuPanelTasks[16].unk_0C                      = flag_value;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.x  = g_MenuPanelTasks[18].pos.x + 5;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.y  = g_MenuPanelTasks[18].pos.y + (g_MenuPanelTasks[18].unk_0B * 16 + 26);
    buttons                                          = INPUT_GetRepeatedButtons(g_InputPressed & (PADLup | PADLdown));
    at_end                                           = g_MenuPanelTasks[16].unk_0B == 3;
    if (buttons & PADLup) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        g_MenuPanelTasks[18].unk_0B -= 1;
        if ((s8)g_MenuPanelTasks[18].unk_0B < 0) {
            g_MenuPanelTasks[18].unk_0B = D_801EC4A4[at_end * 6] - 1;
        }
    } else if (buttons & PADLdown) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        g_MenuPanelTasks[18].unk_0B += 1;
        if ((D_801EC4A4[at_end * 6] - 1) < g_MenuPanelTasks[18].unk_0B) {
            g_MenuPanelTasks[18].unk_0B = 0;
        }
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
        row_index = (u8)at_end;
        FAKE_ORDER_FENCE();
        rows  = D_801EC4A4;
        entry = (rows + row_index * 6 + task->unk_0B)[1];
        if (entry != 0) {
            func_801D9304(entry);
            return;
        }
        next_count                  = D_80148652 + 1;
        entry                       = s_SkillOrderCursors[D_80148656][g_MenuPanelTasks[16].unk_0B];
        g_MenuPanelTasks[16].flags  = 0xFF;
        D_80148652                  = next_count;
        g_MenuPanelTasks[16].unk_0C = entry;
        return;
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        task->active = 0;
        g_MenuStep.state -= 1;
    }
}
