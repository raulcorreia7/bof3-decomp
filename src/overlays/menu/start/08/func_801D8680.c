#include "start_08.h"

extern s8 D_80148656;

#ifdef NON_MATCHING
/* The start menu's skill-order list: the hand cursor walks the rows of the equip
 * slot table (6-byte rows: the count, then its entries), and CONFIRM opens the
 * command the row names. */
NON_MATCHING void func_801D8680(void) {
    s16*           panel;
    MenuPanelTask* task;
    u8*            rows;
    s32            buttons;
    u8             at_end;
    u8             entry;

    Menu_DrawClutStrip(D_80144953);
    panel                                            = &D_801484CC;
    *panel                                           = 0x18;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].active = 1;
    task                                             = (MenuPanelTask*)((u8*)panel + 0xEC);
    g_MenuPanelTasks[18].unk_0C                      = 0xFF;
    g_MenuPanelTasks[16].unk_0C                      = 0xFF;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.x  = g_MenuPanelTasks[18].pos.x + 5;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.y  = g_MenuPanelTasks[18].pos.y + (g_MenuPanelTasks[18].unk_0B * 16 + 26);
    buttons                                          = INPUT_GetRepeatedButtons(g_InputPressed & (PADLup | PADLdown));
    at_end                                           = g_MenuPanelTasks[16].unk_0B == 3;
    if (buttons & PADLup) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        g_MenuPanelTasks[18].unk_0B -= 1;
        if ((s8)g_MenuPanelTasks[18].unk_0B < 0) {
            g_MenuPanelTasks[18].unk_0B = ((u8*)&D_801EC4A4)[at_end * 6] - 1;
        }
    } else if (buttons & PADLdown) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        g_MenuPanelTasks[18].unk_0B += 1;
        if ((((u8*)&D_801EC4A4)[at_end * 6] - 1) < g_MenuPanelTasks[18].unk_0B) {
            g_MenuPanelTasks[18].unk_0B = 0;
        }
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
        rows  = (u8*)&D_801EC4A4;
        entry = (rows + at_end * 6 + task->unk_0B)[1];
        if (entry != 0) {
            func_801D9304(entry);
            return;
        }
        entry                      = s_SkillOrderCursors[D_80148656][g_MenuPanelTasks[16].unk_0B];
        g_MenuPanelTasks[16].flags = 0xFF;
        D_80148652 += 1;
        g_MenuPanelTasks[16].unk_0C = entry;
        return;
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        task->active = 0;
        g_MenuStep.state -= 1;
    }
}
#else
INCLUDE_ASM(func_801D8680);
#endif
