#include "engine/game/00/game_00.h"

/* func_801B78B4 */
/* Runs the ladder transit for the actor's climb direction. */
MATCH void Party_LadderTransitRun(void) {
    g_Game.current->u.field.mode.unsigned_value = 3;
    g_PartyLadderTransits[TASK(Actor)->unk_03]();
}
