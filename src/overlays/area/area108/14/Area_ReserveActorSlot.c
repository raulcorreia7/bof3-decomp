#include "area108_14.h"

/* func_801F4D60 */
MATCH void Area_ReserveActorSlot(void) {
    g_Task->param.actor_slot = Actor_FindFreeSlot();
    if (g_Task->param.actor_slot == GAME_NONE) {
        g_ScriptState->cursor -= 2;
    }
}
