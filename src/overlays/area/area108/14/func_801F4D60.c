#include "area108_14.h"

MATCH void func_801F4D60(void) {
    g_Task->param.actor_slot = Actor_FindFreeSlot();
    if (g_Task->param.actor_slot == GAME_NONE) {
        g_ScriptState->cursor -= 2;
    }
}
