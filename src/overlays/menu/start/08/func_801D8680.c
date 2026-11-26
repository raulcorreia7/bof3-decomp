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

    Menu_DrawClutStrip(g_WindowClut);
    /* FAKE: pure C reaches 92.0% after the panel, table, mask, and counter rewrites. */
    FAKE_HOLD(flag_value, 0xFF);
    panel  = &D_801484CC;
    *panel = 0x18;
    FAKE_USE(flag_value);
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].active = 1;
    task                                           = (MenuPanelTask*)&panel[0x76];
    g_UiPanelTasks[18].unk_0C                      = flag_value;
    g_UiPanelTasks[16].unk_0C                      = flag_value;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].pos.vx = g_UiPanelTasks[18].pos.vx + 5;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].pos.vy = (u16)(g_UiPanelTasks[18].pos.vy + (g_UiPanelTasks[18].unk_0B * 16 + 26));
    buttons                                        = INPUT_GetRepeatedButtons(g_PadStates[0].pressed & (PADLup | PADLdown));
    at_end                                         = g_UiPanelTasks[16].unk_0B == 3;
    if (buttons & PADLup) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        g_UiPanelTasks[18].unk_0B -= 1;
        if ((s8)g_UiPanelTasks[18].unk_0B < 0) {
            g_UiPanelTasks[18].unk_0B = D_801EC4A4[at_end * 6] - 1;
        }
    } else if (buttons & PADLdown) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        g_UiPanelTasks[18].unk_0B += 1;
        if ((D_801EC4A4[at_end * 6] - 1) < g_UiPanelTasks[18].unk_0B) {
            g_UiPanelTasks[18].unk_0B = 0;
        }
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        row_index = (u8)at_end;
        FAKE_ORDER_FENCE();
        rows  = D_801EC4A4;
        entry = (rows + row_index * 6 + task->unk_0B)[1];
        if (entry != 0) {
            func_801D9304(entry);
            return;
        }
        next_count                = D_80148652 + 1;
        entry                     = s_SkillOrderCursors[D_80148656][g_UiPanelTasks[16].unk_0B];
        g_UiPanelTasks[16].flags  = 0xFF;
        D_80148652                = next_count;
        g_UiPanelTasks[16].unk_0C = entry;
        return;
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        task->active = 0;
        g_MenuStep.state -= 1;
    }
}
