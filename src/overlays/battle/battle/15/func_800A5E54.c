#include "battle_15.h"

MATCH void func_800A5E54(void) {
    u8* state;

    if (!(D_801485DC & 1)) {
        state           = &g_BattleRowCursor;
        g_BattleUIStep  = 2;
        g_BattleUIState = 0;
        *state &= 0x7F;
    }
}
