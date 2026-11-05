#include "shop_00.h"

MATCH void func_801D5CB0(void) {
    Menu_DrawHeaderBar(0x14, 0x12, 0x118, 0x13, D_80144952);
    WinDrawCueText(28, 22, D_801E60EC + 0x85);
    func_801DDFB0(0x62, 0x4C, D_801E60F8, LOBU(g_SaveCardPort), 1);
    CardAccessFile(0, 0, 0, 0, 0);
    if (g_SaveCardStatus == CARD_EVENT_OK || g_SaveCardStatus == CARD_EVENT_NEW) {
        if (func_801EF200() != 0) {
            SND_PlayCue(EMI_CUE_ID(1, 7));
            g_SaveCardStatus = 7;
        } else {
            g_SaveCardStatus = 9;
        }
    }
    D_80148652 = 0xC;
}
