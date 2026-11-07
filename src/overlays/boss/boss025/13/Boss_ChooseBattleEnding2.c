#include "boss025_13.h"

MATCH void Boss_ChooseBattleEnding2(void) {
    BOSS_SEND_PARTY_TO_ENDING_POSE(0)
    BOSS_SEND_PARTY_TO_ENDING_POSE(1)
    BOSS_SEND_PARTY_TO_ENDING_POSE(2)
    *g_ScriptVars = 4;
    func_801DDF28();
}
