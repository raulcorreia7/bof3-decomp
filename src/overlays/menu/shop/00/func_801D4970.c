#include "shop_00.h"

MATCH void func_801D4970(void) {
    u8* counter;
    u8  count;

    counter = &D_80148654;
    count   = *counter;
    if (count == 4) {
        SND_PlayCue(EMI_CUE_ID(1, 2));
    }
    MENU_DRAW_HEADER();
    func_801DDFB0(0x62 - *counter * 48, 0x4C, D_801E60F8, g_SaveCardPort, 1);
    count = *counter;
    count--;
    *counter = count;
    if (count == 0) {
        D_80148652 = D_80148652 + 1;
    }
}
