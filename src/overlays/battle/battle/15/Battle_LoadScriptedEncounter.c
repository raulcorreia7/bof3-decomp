#include "battle_15.h"

/* func_800ABBE0 */
MATCH void Battle_LoadScriptedEncounter(void) {
    Battle_LoadEncounterEnemies();
    D_800B5108[g_Battle.encounter]();
}
