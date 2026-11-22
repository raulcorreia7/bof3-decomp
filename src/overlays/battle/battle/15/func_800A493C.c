#include "battle_15.h"

MATCH void func_800A493C(void) {
    u8*  state     = &g_Battle.row_cursor;
    u16* pad_state = &g_PadStates[0].pressed;
    s32  trigger;
    u16  held;

    g_BattleMessages[((D_801EC328 - 1) & 0xF)].text = UI_MessageGetText(*state + 0x42);
    trigger                                         = INPUT_REPEATED(*pad_state, (PADLright | PADLdown | PADLleft));
    held                                            = *pad_state;
    if (held & g_InputMasks[BATTLE_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_Battle.ui_mode += 2;
        return;
    }
    if (held & g_InputMasks[BATTLE_INPUT_CONFIRM]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
        g_Battle.ui_mode += 1;
        return;
    }
    if (trigger & PADLright) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        *state += 1;
    }
    if (trigger & PADLleft) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        *state -= 1;
    }
    if (trigger & PADLdown) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
        *state = 1;
        g_Battle.ui_mode += 1;
        return;
    }
    if ((s8)*state < 0) {
        *state = 2;
    }
    if (*state >= 3) {
        *state = 0;
    }
}
