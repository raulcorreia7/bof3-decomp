#include "shop_00.h"

MATCH void func_801D12FC(void) {
    u16* pad  = &g_InputPressed;
    s8*  mode = (s8*)&D_801E6040;

    D_80148624 = 1;
    D_80148340 = (s8)D_801E6040 + 0x46;
    D_80148628 = D_8014837C + ((s8)D_801E6040 * 0x30) + 4;
    D_8014862A = D_8014837E + 4;
    if (INPUT_REPEATED(*pad, (PADLright | PADLleft)) & (PADLright | PADLleft)) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        D_801E6040 ^= 1;
    }
    if (*pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
        D_80148654 = 5;
        /* signed byte load is required here: retail uses lb, not lbu */
        if (*mode == 0) {
            D_80148651 += 1;
        } else {
            D_80148651 += 2;
        }
        D_80148652 = 0;
    } else if (*pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        g_MenuPanelTasks[0].state = 1;
        D_8014837B                = 1;
        D_80148357                = 1;
        D_80148624                = 0;
        D_80148600                = 0;
        D_80148654                = 5;
        D_80148651 += 3;
    }
}
