#include "boss012_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    u8* status;
    u8  bits;

    status = &g_BattleOutcome.result;
    bits   = *status;
    if (bits & BATTLE_RESULT_VICTORY) {
        g_ScriptVars[0] = 0x23;
        *status         = bits | BATTLE_RESULT_NO_BGM;
        func_801DDED8();
    } else {
        func_801DDF00();
    }
}
