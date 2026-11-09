#include "area155_13.h"

MATCH void func_801F2C04(void) {
    u8* record;
    u8  i;

    if (g_MessageChoice == 2) {
        record = Item_GetRecord(1, 0x4D);
        for (i = 0; i < 12; i++) {
            g_TextVariables[0][i] = record[i];
        }
        D_801490E4[0] = 0;
        if (Item_Add(1, 0x4D, 1, 0) & BYTE_MASK) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x06));
            g_MessageRequest = 0xB;
        } else {
            g_MessageRequest = 0xA;
        }
    } else {
        g_MessageRequest = 0xA;
    }
    SYS_SetFlag(D_80144EF0, 1);
}
