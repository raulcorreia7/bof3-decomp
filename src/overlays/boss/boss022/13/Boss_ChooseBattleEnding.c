#include "boss022_13.h"

MATCH void Boss_ChooseBattleEnding(void) {
    g_ScriptVars[0]    = 0xC;
    g_BattlePartyOrder = 3;
    g_SndBGMId         = 0x6A;
    g_BattlePartyOrder = 3;
    g_Battle.outcome.result |= BATTLE_RESULT_NO_BGM;
    g_Battle.outcome.options &= ~0x40;
    func_801DDF28();
}
