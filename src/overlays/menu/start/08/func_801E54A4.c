#include "start_08.h"

MATCH void func_801E54A4(void) {
    Menu_DrawClutStrip(g_WindowClut);
    MENU_DRAW_HEADER();
    func_801E14A8(0x62, 0x4C, D_801ED870, g_SaveCardPort, 0);
    SAVE_AccessFile(0, 0, 0, 0, 0);
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
        g_SaveCardStatus = SAVE_LOAD_STATUS_NO_FILE;
        /* Join the path where g_SaveCardStatus was already nonzero. */
        goto queue_cue;
    }
queue_cue:
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
    g_MenuStartStep = 0xD;
}
