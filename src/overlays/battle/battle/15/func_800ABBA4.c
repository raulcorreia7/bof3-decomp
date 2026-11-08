#include "battle_15.h"

MATCH void func_800ABBA4(void) {
    if (BATTLE_IS_SCRIPTED()) {
        Battle_LoadScriptedEncounter();
        return;
    }
    func_800ABC30();
}
