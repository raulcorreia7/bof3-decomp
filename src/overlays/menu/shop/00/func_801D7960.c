#include "shop_00.h"

MATCH void func_801D7960(void) {
    u8*  state;
    u32* turns_left;

    func_801D8050(0);
    WinDrawCueText(28, 21, 0x6D);
    state = &D_80148656;
    Menu_DrawInoculationWindow(state[0], 152, 63, 0, D_8014865D);
    Menu_DrawCursorFrame(17, ((s8)state[0] * 0x36 + 0x3E) & 0xFFFE, 128, 52, 0, 6);
    if ((Menu_ChooseYesNo() & BYTE_MASK) != 0) {
        if (D_8014865B != 0) {
            u8 turns;

            turns_left = &g_Zenny;
            turns      = g_Characters[g_Game.members[(s8)state[0]].character_index].level;
            D_8014865B = 0xC;
            D_80148654 = 0x3C;
            D_80148651 += 2;
            *turns_left -= turns * 0xA;
            return;
        }
        SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 6));
        D_80148651 -= 2;
    }
}
