#include "boss013_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    if BATTLE_IS_VICTORY () {
        g_ScriptVars[0] = 0x32;
        Battle_EndVictory();
    } else {
        g_ScriptVars[0] = 0x32;
        Battle_EndToArea();
        g_Game.battle_order = 3;
    }
}
