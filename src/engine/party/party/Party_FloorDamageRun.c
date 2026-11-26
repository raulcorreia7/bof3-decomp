#include "engine/game/00/game_00.h"

/* func_801B91CC */
/* Runs the floor damage sub-step the actor's unk_03 selects. */
MATCH void Party_FloorDamageRun(void) {
    g_PartyFloorDamageSteps[TASK(Actor)->unk_03]();
}
