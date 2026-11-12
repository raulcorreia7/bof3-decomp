#include "start_08.h"

MATCH void func_801E5C68(void) {
    u8* timer;
    u16 step;

    step = 3;
    Menu_DrawClutStrip(D_80144953);
    MENU_DRAW_HEADER();
    g_MenuStartReturnStep = 2;
    switch (g_SaveCardStatus) {
        case CARD_EVENT_TIMEOUT:
            D_801ED7FC = 0xC;
            break;
        case CARD_EVENT_NEW:
            D_801ED7FC = 0xD;
            break;
        case CARD_EVENT_ERROR:
            D_801ED7FC = 0xE;
            break;
        case CARD_EVENT_CAPACITY:
            D_801ED7FC = 0xF;
            break;
        case SAVE_STATUS_LOADED:
            SAVE_DrawSlots(SAVE_SLOTS_X, SAVE_SLOTS_Y, 0U);
            D_801ED7FC            = 0xB;
            g_MenuStartReturnStep = 0xF;
            break;
        case SAVE_STATUS_NO_FILE:
            D_801ED7FC = 0x11;
            break;
        case SAVE_STATUS_BAD_CHECKSUM:
            D_801ED7FC = 0x12;
            break;
        case SAVE_STATUS_NO_CARD:
            D_801ED7FC            = 0xC;
            g_MenuStartReturnStep = 0;
            step                  = 1;
            break;
        default:
            D_801ED7FC = 0x10;
            break;
    }
    UI_DrawText(28, 21, 0, 255U, Message_GetText(D_801ED7FC + 0xA6));
    /* The retail code reaches the countdown byte through its address. */
    if ((g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) != 0 || (g_MenuStartReturnStep == 0xF && --*(timer = &D_80148654) == 0)) {
        if (g_MenuStartReturnStep != 0xF) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
        }
        g_GameEntrySubstate = step;
        g_MenuStartStep     = g_MenuStartReturnStep;
    }
}
