#include "boss054_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    if BATTLE_IS_VICTORY () {
        g_ScriptVars[0] = 50;
        Battle_EndVictory();
    } else {
        Battle_EndDefeat();
    }
}
