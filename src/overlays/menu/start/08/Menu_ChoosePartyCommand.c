#include "start_08.h"

/* func_801D98BC */
MATCH void Menu_ChoosePartyCommand(void) {
    u16* pad;
    s32  prev;
    u8*  slot;
    u8*  cursor;

    Menu_DrawClutStrip(g_WindowClut);
    g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = g_MenuPartyCommand + 0x1F;
    if (g_BattlePanelMode == 0) {
        g_UiPanelTasks[MENU_START_PANEL_CURSOR].active = 1;
        g_UiPanelTasks[MENU_START_PANEL_CURSOR].pos.vx = g_UiPanelTasks[18].pos.vx + (g_MenuPartyCommand * 0x30);
        g_UiPanelTasks[MENU_START_PANEL_CURSOR].pos.vy = g_UiPanelTasks[18].pos.vy + 4;
    } else {
        g_UiPanelTasks[MENU_START_PANEL_CURSOR].active = 0;
    }
    pad                       = &g_PadStates[0].pressed;
    g_UiPanelTasks[18].unk_0B = 0xFF;
    if (INPUT_REPEATED(*pad, (PADLright | PADLleft)) & (PADLright | PADLleft)) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        g_MenuPartyCommand ^= 1;
    }
    if (*pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (g_MenuPartyCommand == 0) {
            Menu_OpenFormation(*pad);
        } else if (g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP) {
            Menu_OpenPartyChange(*pad);
        } else {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
            return;
        }
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
        g_UiPanelTasks[MENU_START_PANEL_CURSOR].active = 0;
        D_80148652                                     = 0;
        D_80148654                                     = 5;
        g_UiPanelTasks[18].unk_0B                      = g_MenuPartyCommand;
        slot                                           = &D_80148651;
        prev                                           = *slot;
        *slot                                          = g_MenuPartyCommand + (prev + 1);
        return;
    }
    if (*pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].state = 1;
        g_BattlePanelMode                                  = 1;
        g_UiPanelTasks[MENU_START_PANEL_CURSOR].active     = 0;
        g_UiPanelTasks[19].active                                         = 0;
        g_UiPanelTasks[20].active                          = 0;
        D_80148652                                         = 0;
        D_80148654                                         = 5;
        cursor                                             = &D_80148651;
        *cursor += 3;
    }
}
