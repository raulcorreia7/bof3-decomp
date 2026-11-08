#include "shop_00.h"

MATCH void func_801D4BBC(void) {
    u8* mode;
    u8  count;
    u8  flag;

    MENU_DRAW_HEADER();
    WinDrawCueText(MENU_PROMPT_X, MENU_PROMPT_Y, D_801E60EC + 0x85);
    SAVE_DrawPortTabs(0x62, 0x4C, D_801E60F8, g_SaveCardPort, 1);
    SAVE_AccessFile(0, 0, 0, 0, 0);
    if (g_SaveCardStatus == CARD_EVENT_OK) {
        func_801D6F00();
        if (g_SaveSlotCount != 0) {
            func_801D7208();
            mode            = &g_MenuStep.state;
            count           = *mode;
            g_SaveSlotCount = 3;
            g_SaveSlotFirst = 0;
            *mode           = count + 1;
            return;
        }
        flag             = D_801E60FC;
        g_SaveCardStatus = flag ? SAVE_STATUS_NO_FILE : CARD_EVENT_CAPACITY;
    }
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
    g_MenuStep.state = 0xC;
}
