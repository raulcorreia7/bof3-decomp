#include "battle_15.h"

MATCH void func_800A493C(void) {
    u8*  state     = &g_BattleRowCursor;
    u16* pad_state = &g_InputPressed;
    s32  trigger;
    u16  held;

    D_801EB5B4[((D_801EC328 - 1) & 0xF) * 2] = Resource_GetText(*state + 0x42);
    trigger                                  = INPUT_REPEATED(*pad_state, (PADLright | PADLdown | PADLleft));
    held                                     = *pad_state;
    if (held & g_InputMasks[INPUT_SLOT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        g_BattleUIState += 2;
        return;
    }
    if (held & g_InputMasks[INPUT_SLOT_CONFIRM]) {
        SND_PlayCue(EMI_CUE_ID(1, 4));
        g_BattleUIState += 1;
        return;
    }
    if (trigger & PADLright) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
        *state += 1;
    }
    if (trigger & PADLleft) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
        *state -= 1;
    }
    if (trigger & PADLdown) {
        SND_PlayCue(EMI_CUE_ID(1, 4));
        *state = 1;
        g_BattleUIState += 1;
        return;
    }
    if ((s8)*state < 0) {
        *state = 2;
    }
    if (*state >= 3) {
        *state = 0;
    }
}
