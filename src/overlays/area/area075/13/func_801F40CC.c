#include "area075_13.h"

MATCH void func_801F40CC(void) {
    u8* state;
    u8  index;
    u8  step;
    u8  seq;
    u8  count;
    s32 result;

    state = &D_801F58C3;
    index = state[0];
    if (D_801F58CA < 0x1F5) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 1));
        if (D_801F5890[index][2] != 0) {
            g_Self = &g_Actors[D_801F58D1];
            Script_Request(D_801F5890[index][2]);
            SELF(Actor)->mirror = 0;
        }
        result = 4;
    } else {
        D_801F58C7 = 0;
        D_801F58C8 = 0;
        D_801F58C9 = D_801F5870[rand() & 0xF];
        /* FAKE: cse folds the constant base into absolute symbol loads. */
        FAKE_OPAQUE(state);
        state[0x10] += 1;
        if (state[0x10] >= D_801F5858[state[0xF]].count) {
            state[0xF]  = D_801F5880[rand() & 0xF];
            state[0x10] = 0;
        }
        seq        = state[0xF];
        count      = state[0x10];
        step       = D_801F5858[seq].steps[count * 2] - 1;
        state[0]   = step;
        D_801F58C4 = D_801F5858[seq].steps[count * 2 + 1];
        if (D_801F5890[index][step] != 0) {
            g_Self = &g_Actors[D_801F58D1];
            Script_Request(D_801F5890[index][step]);
            SELF(Actor)->mirror = 0;
        }
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 1));
        result = 2;
    }
    D_801F58C0 = result;
}
