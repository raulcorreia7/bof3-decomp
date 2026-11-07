#include "shop_00.h"

MATCH void func_801DFDF4(void) {
    s8*  toggle;
    u16* pad;
    s32  side;
    u8   ff;
    u8   count;
    u8   tbl;
    u8   tbl2;
    /* FAKE: pin keeps the shared constant 2 in the retail v1 home. */
    MATCH_REG(u8, two, "v1");

    toggle     = &D_8014865B;
    pad        = &g_InputPressed;
    D_80148340 = 0x36;
    D_80148624 = 1;
    side       = 1 - *toggle;
    D_80148628 = D_80148334 + (side << 5) + 0xDE;
    D_8014862A = D_80148336 + 5;
    if (*pad & (PADLright | PADLleft)) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
        *toggle ^= 1;
    }
    if (*pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (*toggle != 0) {
            SND_PlayCue(EMI_CUE_ID(1, 4));
            SND_PlayCue(EMI_CUE_ID(1, 2));
            D_801E625C = 0;
            Item_Remove(ITEM_CAT_ITEM, ITEM_SKILL_INK, 1, 0);
            two         = 2;
            D_80148379  = 7;
            D_8014837A  = 0xD;
            D_8014837B  = two;
            *D_80148378 = 1;
            tbl         = D_801E6264[D_801E625C];
            D_8014839F  = two;
            /* FAKE: the order lock steers regalloc */
            ORDER_LOCK_BEGIN
                count      = D_80148652;
                D_8014837C = -0x96;
            ORDER_LOCK_END;
            /* FAKE: the order lock steers regalloc */
            ORDER_LOCK_BEGIN
                D_8014837E = 0x74;
                D_8014839E = 0xC;
                ff         = 0xFF;
                D_8014839D = 7;
                D_8014839C = 1;
                D_80148382 = tbl;
            ORDER_LOCK_END;
            tbl2 = D_801E6264[D_801E625C];
            /* FAKE: the order lock steers the tail block's scheduling. */
            ORDER_LOCK_BEGIN
                count++;
                D_801483A8 = ff;
                D_801483A0 = BATTLE_PARTY_STRIDE;
                D_801483A7 = 0;
                D_801483A9 = 0;
                D_801483A2 = 0x3E;
                D_80148652 = count;
                D_801483A6 = tbl2;
            ORDER_LOCK_END;
            return;
        }
        SND_PlayCue(EMI_CUE_ID(1, 6));
        D_80148651 -= 1;
        return;
    }
    if (*pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        D_80148651 -= 1;
    }
}
