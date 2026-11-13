#include "start_08.h"

s32 func_801DAC1C(u16);

MATCH void func_801D98BC(void) {
    u16* pad;
    s32  prev;
    u8*  slot;
    u8*  cursor;

    Menu_DrawClutStrip(D_80144953);
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = D_801ED68C + 0x1F;
    if (g_BattlePanelMode == 0) {
        g_MenuPanelTasks[MENU_START_PANEL_CURSOR].active = 1;
        g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.x  = g_MenuPanelTasks[18].pos.x + (D_801ED68C * 0x30);
        g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.y  = g_MenuPanelTasks[18].pos.y + 4;
    } else {
        g_MenuPanelTasks[MENU_START_PANEL_CURSOR].active = 0;
    }
    pad                         = &g_InputPressed;
    g_MenuPanelTasks[18].unk_0B = 0xFF;
    if (INPUT_REPEATED(*pad, (PADLright | PADLleft)) & (PADLright | PADLleft)) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        D_801ED68C ^= 1;
    }
    if (*pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (D_801ED68C == 0) {
            func_801DAC1C(*pad);
        } else if (g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP) {
            func_801DAE14(*pad);
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
            return;
        }
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
        g_MenuPanelTasks[MENU_START_PANEL_CURSOR].active = 0;
        D_80148652                                       = 0;
        D_80148654                                       = 5;
        g_MenuPanelTasks[18].unk_0B                      = D_801ED68C;
        slot                                             = &D_80148651;
        prev                                             = *slot;
        *slot                                            = D_801ED68C + (prev + 1);
        return;
    }
    if (*pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].state = 1;
        g_BattlePanelMode                                    = 1;
        g_MenuPanelTasks[MENU_START_PANEL_CURSOR].active     = 0;
        D_801485DC                                           = 0;
        g_MenuPanelTasks[20].active                          = 0;
        D_80148652                                           = 0;
        D_80148654                                           = 5;
        cursor                                               = &D_80148651;
        *cursor += 3;
    }
}
