#include "battle_03.h"

MATCH void func_801D3280(void) {
    if (D_801463C2 == 0) {
        g_BattleStep    = 3;
        g_BattleSubStep = 0;
        g_BattleUIStep  = 0;
        g_BattleState |= BATTLE_STATE_EFFECT_PLAYING;
    }
}
