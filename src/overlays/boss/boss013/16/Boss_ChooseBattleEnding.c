#include "boss013_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    if BATTLE_IS_VICTORY () {
        g_ScriptVars[0] = 0x32;
        func_801DDED8();
    } else {
        g_ScriptVars[0] = 0x32;
        func_801DDF28();
        g_Game.battle_order = 3;
    }
}
