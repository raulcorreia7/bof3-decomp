#include "start_08.h"

MATCH void func_801E54A4(void) {
    Menu_DrawClutStrip(D_80144953);
    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, D_80144952);
    func_801E14A8(0x62, 0x4C, D_801ED870, LOBU(g_SaveCardPort), 0);
    CardAccessFile(0, 0, 0, 0, 0);
    g_SaveSlotFirst = 0;
    if (g_SaveCardStatus == CARD_EVENT_OK) {
        g_SaveSlotCount = func_801EFCA8(g_SaveFileNameFormat, 0x10);
        if (g_SaveCardDirectory[0] != 0) {
            func_801E77F0();
            g_SaveSlotCount  = 3;
            g_MenuStartTimer = 0;
            g_MenuStartStep += 1;
            return;
        }
        g_SaveCardStatus = SAVE_STATUS_NO_FILE;
        /* Join the path where g_SaveCardStatus was already nonzero. */
        goto queue_cue;
    }
queue_cue:
    SND_PlayCue(EMI_CUE_ID(1, 7));
    g_MenuStartStep = 0xD;
}
