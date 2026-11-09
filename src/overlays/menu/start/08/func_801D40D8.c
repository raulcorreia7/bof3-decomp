#include "start_08.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801D40D8(void) {
    u8*  flag;
    s8*  label;
    u16* pad;
    u8** records;

    Menu_DrawClutStrip(D_80144953);
    flag = &D_80148624;
    Message_SetVariable(0, 0xC,
                        Item_GetRecord(g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A,
                                       D_801C893C[D_8014850E][g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C]));
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = 0x1A;
    label                                                       = &D_8014865B;
    *flag                                                       = 1;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.x =
        g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].pos.x + ((1 - *label) << 5) + 0xDE;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.y = g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].pos.y + 5;
    pad                                             = &g_InputPressed;
    records                                         = D_801C893C;
    if (*pad & (PADLright | PADLleft)) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        *label ^= 1;
    }
    if (g_InputMasks[MENU_INPUT_CONFIRM] & *pad) {
        if (*label != 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
            records[g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A][g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C] =
                0;
            D_801C8950[g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A]
                      [g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C] = 0;
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        }
        g_MenuStep.sub_step -= 3;
        /* FAKE: retail reaches the neighbouring flag through the record base. */
        *(s8*)((u8*)flag - 0x113) = -1;
        return;
    }
    if (g_InputMasks[MENU_INPUT_CANCEL] & *pad) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        *(s8*)((u8*)flag - 0x113) = -1;
        g_MenuStep.sub_step -= 3;
    }
}
#else
INCLUDE_ASM(func_801D40D8);
#endif
