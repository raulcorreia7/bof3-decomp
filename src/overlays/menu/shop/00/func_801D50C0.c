#include "shop_00.h"

MATCH void func_801D50C0(void) {
    u8 count;

    MENU_DRAW_HEADER();
    WinDrawCueText(28, 22, 0x9F);
    SAVE_DrawSlots(0x20, 0x30, 0);
    if ((Menu_ToggleOption() & BYTE_MASK) != 0) {
        if (D_8014865B != 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
            count      = D_80148652;
            D_801E60EC = SAVE_WAIT_OVERWRITE;
            D_80148652 = 0x13;
            D_80148654 = 2;
            D_801E6094 = ++count;
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
            D_80148652--;
        }
    }
}
