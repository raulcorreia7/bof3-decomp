#include "shop_00.h"

MATCH void func_801D4BBC(void) {
    u8* mode;
    u8  count;
    u8  flag;

    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    WinDrawCueText(28, 22, D_801E60EC + 0x85);
    func_801DDFB0(0x62, 0x4C, D_801E60F8, g_SaveCardPort, 1);
    CardAccessFile(0, 0, 0, 0, 0);
    if (g_SaveCardStatus == CARD_EVENT_OK) {
        func_801D6F00();
        if (g_SaveSlotCount != 0) {
            func_801D7208();
            mode            = &D_80148652;
            count           = *mode;
            g_SaveSlotCount = 3;
            g_SaveSlotFirst = 0;
            *mode           = count + 1;
            return;
        }
        flag             = D_801E60FC;
        g_SaveCardStatus = flag ? SAVE_STATUS_NO_FILE : CARD_EVENT_CAPACITY;
    }
    SND_PlayCue(EMI_CUE_ID(1, 7));
    D_80148652 = 0xC;
}
