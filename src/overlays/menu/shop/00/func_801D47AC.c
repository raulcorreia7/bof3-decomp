#include "shop_00.h"

MATCH void func_801D47AC(void) {
    s32 first_status;
    s32 second_status;
    u8  count;

    Menu_DrawHeaderBar(0x14, 0x12, 0x118, 0x13, D_80144952);
    WinDrawCueText(28, 22, D_801E60EC + 0x85);
    g_SaveCardPort = 0;
    CardAccessFile(0, 0, 0, 0, 0);
    first_status   = g_SaveCardStatus;
    g_SaveCardPort = 1;
    CardAccessFile(0, 0, 0, 0, 0);
    second_status = g_SaveCardStatus;
    if (first_status == CARD_EVENT_OK || first_status == CARD_EVENT_NEW) {
        if (second_status == CARD_EVENT_OK || second_status == CARD_EVENT_NEW) {
            D_801E608C     = 1;
            g_SaveCardPort = 0;
            D_801E6088     = 0;
            D_801E60F8     = 3;
        } else {
            g_SaveCardPort = 0;
            D_801E6088     = 0;
            D_801E608C     = 0;
            D_801E60F8     = 1;
        }
    } else if (second_status == CARD_EVENT_OK || second_status == CARD_EVENT_NEW) {
        D_801E6088     = 1;
        D_801E608C     = 1;
        g_SaveCardPort = 1;
        D_801E60F8     = 2;
    } else {
        SND_PlayCue(EMI_CUE_ID(1, 7));
        D_80148652 = 0xC;
        D_801E60F8 = 0;
        return;
    }
    count      = D_80148652;
    D_80148654 = 4;
    D_80148652 = count + 1;
}
