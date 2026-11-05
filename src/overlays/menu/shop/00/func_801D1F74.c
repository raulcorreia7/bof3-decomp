#include "shop_00.h"

MATCH void func_801D1F74(void) {
    u8*  block;
    s8*  mode;
    u16* pad;
    u16  pad_state;
    s16  count;

    block = Item_GetRecord(g_ShopItemCategory, g_ShopItemId);
    mode  = &D_8014865B;
    pad   = &g_InputPressed;
    TEXT_SetVariable(0, 0xC, block);
    D_80148340 = 0x4A;
    D_80148624 = 1;
    D_80148628 = D_80148334 + (1 - *mode) * 32 + 0xDE;
    D_8014862A = D_80148336 + 5;
    if (*pad & (PADLright | PADLleft)) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
        *mode = *mode ^ 1;
    }
    pad_state = *pad;
    if ((pad_state & D_80145AC2) == 0) {
        if ((pad_state & D_80145AC4) == 0) {
            return;
        }
    } else if (*mode != 0) {
        SND_PlayCue(EMI_CUE_ID(1, 3));
        D_80148656 = 0;
        count      = D_80148652 + 1;
        goto store; /* store the computed value */
    }
    SND_PlayCue(EMI_CUE_ID(1, 6));
    count = D_80148652 - 3;
store:
    D_80148652 = count;
}
