#include "start_08.h"

/* Runs the command-row cursor of the start menu: moves D_801ED648 on
 * left/right, then on confirm advances the menu step by the chosen row, or on
 * cancel backs out to the previous panel. */
MATCH void func_801D7314(void) {
    s32 buttons;
    u8  old;

    Menu_DrawClutStrip(g_WindowClut);
    g_UiPanelTasks[16].unk_08                                 = 0;
    g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = (&D_801EC488)[(s8)D_801ED648];
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].active            = 1;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].pos.vx            = g_UiPanelTasks[MENU_START_PANEL_COMMANDS].pos.vx + (s8)D_801ED648 * 0x30;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].pos.vy            = g_UiPanelTasks[MENU_START_PANEL_COMMANDS].pos.vy + 4;
    g_UiPanelTasks[MENU_START_PANEL_COMMANDS].unk_0B          = 0xFF;
    buttons                                                   = INPUT_GetRepeatedButtons(g_PadStates[0].pressed & (PADLright | PADLleft));
    old                                                       = D_801ED648;
    if (buttons & PADLleft) {
        D_801ED648 = old - 1;
        if ((s8)(old - 1) < 0) {
            D_801ED648 = 3;
        }
    }
    if (buttons & PADLright) {
        D_801ED648 += 1;
        if ((s8)D_801ED648 >= 4) {
            D_801ED648 = 0;
        }
    }
    if ((s8)old != (s8)D_801ED648) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        g_UiPanelTasks[MENU_START_PANEL_COMMANDS].unk_0B = D_801ED648;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
        if (D_801ED648 == 1) {
            u8* step = &D_80148651;

            D_80148652 = 0;
            *step      = *step + 5;
            return;
        }
        if (D_801ED648 == 3) {
            g_BattleChoicePhase = 1;
            D_80148654          = 7;
            D_80148652          = 0;
            D_80148651 += 7;
            return;
        }
        if (D_801ED648 == 2) {
            g_UiPanelTasks[16].unk_0B = 3;
        }
        {
            u8* last = &D_80148651;

            *last = *last + 1;
        }
    } else if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        u8* step = &D_80148651;

        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].state = 1;
        g_UiPanelTasks[MENU_START_PANEL_COMMANDS].state    = 1;
        g_BattleChoicePhase                                = 1;
        g_UiPanelTasks[MENU_START_PANEL_CURSOR].active     = 0;
        D_80148654                                         = 5;
        *step                                              = *step + 6;
    }
}
