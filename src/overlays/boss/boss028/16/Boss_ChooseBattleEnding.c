#include "boss028_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    if BATTLE_IS_VICTORY () {
        g_ScriptVars[0] = 30;
        Battle_EndVictory();
    } else {
        Battle_EndDefeat();
    }
}
