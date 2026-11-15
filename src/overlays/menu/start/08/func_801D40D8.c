#include "start_08.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801D40D8(void) {
    u8*  flag;
    s8*  label;
    u16* pad;
    u8** records;

    Menu_DrawClutStrip(D_80144953);
    flag = &D_80148624;
    Message_SetVariable(0, 0xC, Item_GetRecord(D_8014850E, D_801C893C[D_8014850E][D_80148510]));
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = 0x1A;
    label                                                       = &D_8014865B;
    *flag                                                       = 1;
    pad                                                         = &g_InputPressed;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.x             = g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].pos.x + ((1 - *label) << 5) + 0xDE;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.y             = g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].pos.y + 5;
    records                                                     = D_801C893C;
    if (*pad & (PADLright | PADLleft)) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        *label ^= 1;
    }
    if (*pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (*label != 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
            records[D_8014850E][D_80148510]    = 0;
            D_801C8950[D_8014850E][D_80148510] = 0;
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        }
        {
            u8* step = &D_80148651;

            *step -= 3;
        }
        D_80148504.drawn_cursor = 0xFF;
        return;
    }
    if (*pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        *(u8*)&D_80148511 = 0xFF;
        D_80148651 -= 3;
    }
}
#else
INCLUDE_ASM(func_801D40D8);
#endif
