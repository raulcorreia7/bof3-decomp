#include "shop_00.h"

MATCH void func_801D4DB4(void) {
    u8* counter;
    u8  count;

    counter = &D_80148654;
    count   = *counter;
    if (count == 4) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
    }
    MENU_DRAW_HEADER();
    SAVE_DrawSlots((SAVE_SLOTS_X - *counter * 0x50), SAVE_SLOTS_Y, 1);
    count = *counter;
    count--;
    *counter = count;
    if (count == 0) {
        D_80148652 = D_80148652 + 1;
    }
}
