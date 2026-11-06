#include "shop_00.h"

MATCH void func_801D7960(void) {
    u8*  state;
    u32* turns_left;

    func_801D8050(0);
    WinDrawCueText(28, 21, 0x6D);
    state = &D_80148656;
    func_801D7E1C(state[0], 0x98, 0x3F, 0, D_8014865D);
    Menu_DrawCursorFrame(0x11, ((s8)state[0] * 0x36 + 0x3E) & 0xFFFE, 0x80, 0x34, 0, 6);
    if ((Menu_ToggleOption() & BYTE_MASK) != 0) {
        if (D_8014865B != 0) {
            u8 turns;

            turns_left = &g_Zenny;
            turns      = g_Characters[D_80145FCC[(s8)state[0]][0]].level;
            D_8014865B = 0xC;
            D_80148654 = 0x3C;
            D_80148651 += 2;
            *turns_left -= turns * 0xA;
            return;
        }
        SND_PlayCue(EMI_CUE_ID(1, 6));
        D_80148651 -= 2;
    }
}
