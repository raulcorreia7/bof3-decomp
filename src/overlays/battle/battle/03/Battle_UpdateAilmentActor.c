#include "battle_03.h"

/* func_801E6C84 */
MATCH void Battle_UpdateAilmentActor(void) {
    BattleAilmentActorSteps handlers;

    handlers = g_BattleAilmentActorSteps;
    if (g_Battle.phase.mode != BATTLE_MODE_RESULT) {
        g_Scripts = BATTLE_SCRIPT_TABLE;
        handlers.steps[SELF(PartyMember)->header.mode]();
        g_Scripts = AREA_SCRIPT_TABLE;
    }
}
