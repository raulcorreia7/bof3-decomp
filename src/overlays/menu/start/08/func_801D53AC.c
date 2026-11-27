#include "start_08.h"

MATCH void func_801D53AC(void) {
    s32 pressed;
    u8  old;

    Menu_DrawClutStrip(g_WindowClut);
    g_UIPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = D_801EC440[(s8)D_801ED620];
    g_UIPanelTasks[MENU_START_PANEL_CURSOR].active            = 1;
    g_UIPanelTasks[MENU_START_PANEL_CURSOR].pos.vx            = (u16)g_UIPanelTasks[MENU_START_PANEL_COMMANDS].pos.vx + (s8)D_801ED620 * 0x30;
    g_UIPanelTasks[MENU_START_PANEL_CURSOR].pos.vy            = (u16)g_UIPanelTasks[MENU_START_PANEL_COMMANDS].pos.vy + 4;
    g_UIPanelTasks[MENU_START_PANEL_ITEMS].flags              = 1;
    g_UIPanelTasks[MENU_START_PANEL_COMMANDS].unk_0B          = 0xFF;
    pressed                                                   = INPUT_GetRepeatedButtons(g_PadStates[0].pressed & (PADLright | PADLleft));
    old                                                       = D_801ED620;
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
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
        g_UIPanelTasks[MENU_START_PANEL_CURSOR].active   = 0;
        g_UIPanelTasks[MENU_START_PANEL_COMMANDS].unk_0B = D_801ED620;
        g_MenuStep.sub_step++;
        return;
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        u8* step;

        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        step                                               = &g_MenuStep.sub_step;
        g_UIPanelTasks[MENU_START_PANEL_DESCRIPTION].state = 1;
        g_UIPanelTasks[MENU_START_PANEL_COMMANDS].state    = 1;
        g_UIPanelTasks[MENU_START_PANEL_ITEMS].state       = 1;
        D_801485DC                                         = 0;
        g_UIPanelTasks[MENU_START_PANEL_CURSOR].active     = 0;
        D_80148654                                         = 0;
        *step += 5;
    }
}
