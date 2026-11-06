#include "shop_00.h"

/* shop_00.h declares CardAccessFile void; this unit reads its s8 result. */
typedef s8 (*SaveProbe)(s32, s32, s32, s32, s32);

MATCH void func_801D5894(void) {
    char date_label[0x18];
    char save_name[0x40];

    g_SaveSlotCount = 3;
    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    WinDrawCueText(28, 22, D_801E60EC + 0x85);
    SAVE_DrawSlots(0x20, 0x30, 0);
    CardAccessFile(0, 0, 0, 0, 0);
    if (g_SaveCardStatus == CARD_EVENT_OK) {
        sprintf((char*)g_UiFormatBuffer, D_801D0C20, g_SaveSlotFirst);
        sprintf((char*)g_UiFormatBuffer, D_801D0C68, g_PlayClock.hours, g_PlayClock.minutes, g_PlayClock.seconds);
        strcpy(save_name, (char*)g_UiFormatBuffer);
        sprintf((char*)g_UiFormatBuffer, D_801D0C20, g_SaveSlotFirst);
        strcpy(date_label, (char*)g_UiFormatBuffer);
        if (((SaveProbe)CardAccessFile)(1, date_label, 0x200, 0, 0) != -1) {
            D_801E6108 = g_SaveSlotFirst + 1;
            SAVE_BuildSlotImage();
            if (D_801E60FC != 0) {
                D_801E60FC -= 1;
                D_801E610C += 1;
            }
            if (((SaveProbe)CardAccessFile)(1, date_label, 2, SAVE_FILE_SIZE, 0) != -1) {
                g_SaveCardStatus = SAVE_STATUS_CREATED;
                D_80148652       = 0xC;
                D_80148654       = 0x3C;
                D_801E60F0       = 2;
                return;
            }
        }
        if (g_SaveCardStatus == CARD_EVENT_ERROR) {
            g_SaveCardStatus = SAVE_STATUS_WRITE_FAILED;
        }
        SND_PlayCue(EMI_CUE_ID(1, 7));
    }
    D_80148652 = 0xC;
}
