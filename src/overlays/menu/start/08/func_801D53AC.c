#include "start_08.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801D53AC(void) {
    s32 pressed;
    u8  old;

    Menu_DrawClutStrip(D_80144953);
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].active            = 1;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.y             = (u16)g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].pos.y + 4;
    g_MenuPanelTasks[MENU_START_PANEL_ITEMS].flags              = 1;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.x             = (u16)g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].pos.x + (s8)D_801ED620 * 0x30;
    g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].unk_0B          = 0xFF;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = D_801EC440[(s8)D_801ED620];
    pressed                                                     = INPUT_GetRepeatedButtons(g_InputPressed & (PADLright | PADLleft));
    old                                                         = D_801ED620;
    if (pressed & PADLleft) {
        D_801ED620 = old - 1;
        if ((s8)(old - 1) < 0) {
            D_801ED620 = 3;
        }
    }
    if (pressed & PADLright) {
        D_801ED620 += 1;
        if ((s8)D_801ED620 >= 4) {
            D_801ED620 = 0;
        }
    }
    if ((s8)old != (s8)D_801ED620) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        u8* step;

        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
        step                                               = &g_MenuStep.sub_step;
        g_MenuPanelTasks[MENU_START_PANEL_CURSOR].active   = 0;
        g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].unk_0B = D_801ED620;
        *step += 1;
        return;
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        u8* step;

        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        step                                                 = &g_MenuStep.sub_step;
        g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].state = 1;
        g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].state    = 1;
        g_MenuPanelTasks[MENU_START_PANEL_ITEMS].state       = 1;
        D_801485DC                                           = 0;
        g_MenuPanelTasks[MENU_START_PANEL_CURSOR].active     = 0;
        D_80148654                                           = 0;
        *step += 5;
    }
}
#else
INCLUDE_ASM(func_801D53AC);
#endif
