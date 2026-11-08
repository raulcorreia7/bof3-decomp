#include "battle_15.h"

MATCH void func_800ABBE0(void) {
    Battle_LoadEncounterEnemies();
    D_800B5108[g_Battle.encounter]();
}
