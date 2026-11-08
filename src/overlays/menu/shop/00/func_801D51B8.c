#include "shop_00.h"

/* shop_00.h declares SAVE_AccessFile void; this unit reads its s8 result. */
typedef s8 (*SaveProbe)(s32, s32, s32, s32, s32);

MATCH void func_801D51B8(void) {
    u8* name;

    name = &g_WindowStyle;
    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, *name);
    WinDrawCueText(28, 22, D_801E60EC + 0x85);
    SAVE_DrawSlots(0x20, 0x30, 0);
    SAVE_AccessFile(0, 0, 0, 0, 0);
    if (g_SaveCardStatus == CARD_EVENT_OK) {
        TEXT_Format(g_UiFormatBuffer, D_801D0C20, g_SaveSlotFirst);
        if (((SaveProbe)SAVE_AccessFile)(1, g_UiFormatBuffer, 1, 1, 0) != -1) {
            TEXT_Format(g_UiFormatBuffer, D_801D0C20, g_SaveSlotFirst);
            D_801E6108 = D_80145AE5 + 0xD1;
            SAVE_BuildSlotImage();
            TEXT_Format(g_UiFormatBuffer, D_801D0C20, g_SaveSlotFirst);
            if (((SaveProbe)SAVE_AccessFile)(1, g_UiFormatBuffer, 2, SAVE_FILE_SIZE, 0) != -1) {
                func_801D6CE4(g_SaveSlotFirst, name - 0x7A);
                g_SaveCardStatus = SAVE_STATUS_SAVED;
                D_80148652       = 0xC;
                D_80148654       = 0x3C;
                D_801E60F0       = 2;
                return;
            }
        }
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
    }
    D_80148652 = 0xC;
}
