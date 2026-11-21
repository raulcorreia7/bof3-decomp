#include "engine/game/00/game_00.h"

/* func_801AD3B4 */
MATCH void FieldAction_React(void) {
    u32 choice;

    choice = RANDOM_MASK(0xF);
    if ((g_Task->option_flags & ACTOR_OPT_ROUTE_LOCKED) == 0) {
        Actor_DispatchSelectorScript(((g_Game.members[0].facing ^ 0x4) & 0x7));
    }
    Actor_SpawnSceneActor(choice >= 7 ? 2 : 3);
    g_GameFlags |= GAME_FLAG_SCRIPT_ACTIVE;
    g_Task->unk_04 = 1;
}
