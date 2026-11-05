#include "shop_00.h"

MATCH void func_801D4DB4(void) {
    u8* counter;
    u8  count;

    counter = &D_80148654;
    count   = *counter;
    if (count == 4) {
        SND_PlayCue(EMI_CUE_ID(1, 2));
    }
    Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, D_80144952);
    SAVE_DrawSlots((s16)(0x20 - *counter * 0x50), 0x30, 1);
    count = *counter;
    count--;
    *counter = count;
    if (count == 0) {
        D_80148652 = D_80148652 + 1;
    }
}
