#include "boss024_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    volatile u8* status;
    u8           bits;

    status = &g_BattleResult;
    bits   = *status;
    if (bits & BATTLE_RESULT_VICTORY) {
        g_ScriptVars[0] = 5;
        *status         = bits | BATTLE_RESULT_NO_BGM;
        g_SndBGMId      = 0x44;
        func_801DDED8();
    } else {
        func_801DDF00();
    }
}
