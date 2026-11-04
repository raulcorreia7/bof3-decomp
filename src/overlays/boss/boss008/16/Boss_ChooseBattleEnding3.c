#include "boss008_16.h"

MATCH void Boss_ChooseBattleEnding3(void) {
    if BATTLE_IS_VICTORY () {
        g_ScriptVars[0] = 0x30;
        func_801DDED8();
    } else {
        func_801DDF00();
    }
}
