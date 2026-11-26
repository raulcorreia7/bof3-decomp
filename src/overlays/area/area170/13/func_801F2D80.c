#include "area170_13.h"

MATCH void func_801F2D80(void) {
    Actor* work;
    u8     old;

    old = MEM_PTR(u8, SELF(Actor)->unk_4C)[0];
    if ((g_PadStates[0].pressed & PADLleft) != 0) {
        MEM_PTR(u8, SELF(Actor)->unk_4C)[0] = old + 1;
        if (MEM_PTR(u8, SELF(Actor)->unk_4C)[0] >= 9) {
            MEM_PTR(u8, SELF(Actor)->unk_4C)[0] = 0;
        }
    }
    if ((g_PadStates[0].pressed & PADLright) != 0) {
        MEM_PTR(u8, SELF(Actor)->unk_4C)[0] -= 1;
        if (MEM_PTR(s8, SELF(Actor)->unk_4C)[0] < 0) {
            MEM_PTR(u8, SELF(Actor)->unk_4C)[0] = 8;
        }
    }
    if (old != MEM_PTR(u8, SELF(Actor)->unk_4C)[0]) {
        SND_SEPlay(0x204);
    }

    if ((g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) != 0) {
        SND_SEPlay(0x205);
        work                     = SELF(Actor);
        D_801F5990[work->unk_06] = MEM_PTR(u8, work->unk_4C)[0];
        D_801448EE               = 1;
        SELF(Actor)->header.mode += 1;
    } else if ((g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) != 0) {
        SND_SEPlay(0x206);
        D_801448EE = 0xFF;
        SELF(Actor)->header.mode += 2;
    }

    func_801F31DC(LOH(SELF(Actor)->screen_x), LOH(SELF(Actor)->screen_y));
}
