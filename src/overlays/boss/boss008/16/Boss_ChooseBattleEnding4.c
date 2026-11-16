#include "boss008_16.h"

MATCH void Boss_ChooseBattleEnding4(void) {
    if BATTLE_IS_VICTORY () {
        g_ScriptVars[0] = 0x44;
        Battle_EndVictory();
    } else {
        Battle_EndDefeat();
    }
}
