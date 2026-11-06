#include "start_08.h"

extern u8 g_SndMono;

MATCH void SAVE_RunLoadVerify(void) {
    u32* clear;
    u8*  src;
    u8*  dst;
    /* FAKE: retail keeps the byte count in a0. */
    MATCH_REG(u16, i, "a0");
    u16 stored;
    u32 sum;

    Menu_DrawClutStrip(D_80144953);
    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    SAVE_DrawSlots(0x20, 0x30, 0);
    CardAccessFile(0, 0, 0, 0, 0);
    if (g_SaveCardStatus != CARD_EVENT_OK) {
        SND_PlayCue(EMI_CUE_ID(1, 7));
    } else {
        clear = MEM_PTR(u32, SAVE_IMAGE_ADDR);
        for (i = 0; i < 1792; i++) {
            *clear++ = 0;
        }
        sprintf((char*)g_UiFormatBuffer, g_SaveFileNameFormat, g_SaveSlotFirst);
        if (CardAccessFile(1, g_UiFormatBuffer, 1, SAVE_FILE_SIZE, 0) != -1) {
            stored     = D_800C1A70;
            D_800C1A70 = 0;
            sum        = 0;
            src        = MEM_PTR(u8, SAVE_IMAGE_ADDR);
            dst        = &D_801448D8;
            for (i = 0; i < SAVE_CHECKSUM_LENGTH; i++) {
                *dst = *src;
                sum += *src++;
                dst++;
            }
            g_GameFlags = D_80145025;
            if ((sum & SAVE_CHECKSUM_MASK) != stored) {
                SND_PlayCue(EMI_CUE_ID(1, 7));
                g_SaveCardStatus = SAVE_STATUS_BAD_CHECKSUM;
            } else {
                if (g_SndMono == 0) {
                    SsSetStereo();
                } else {
                    SsSetMono();
                }
                D_80148654       = 0x3C;
                g_SaveCardStatus = SAVE_STATUS_LOADED;
            }
        }
    }
    g_MenuStartStep = 0xD;
}
