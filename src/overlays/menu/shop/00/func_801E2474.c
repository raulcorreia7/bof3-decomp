#include "shop_00.h"

/* File-local declarations: the shop message panel fields and the pad halfwords
 * are not declared by this target's shop_00.h. */

MATCH void func_801E2474(void) {
    u8* counter;
    u8  count;

    D_80148340 = D_80148361 + 0x122;
    D_80148360 = D_8014835F;

    counter = &D_80148654;
    count   = *counter;
    if (count != 0) {
        *counter = count - 1;
        return;
    }
    if ((g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) != 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
        D_80148357 = 2;
        D_8014837B = 1;
        D_8014839F = 1;
        D_80148360 = 0x7F;
        *counter   = 8;
        D_80148652++;
    }
}
