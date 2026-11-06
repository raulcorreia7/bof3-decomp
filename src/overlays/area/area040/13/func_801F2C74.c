#include "area040_13.h"

MATCH void func_801F2C74(void) {
    Actor* actor;

    if (g_GameState->slot_index_79 == 2) {
        actor = g_Task;
        actor->pos.x.fixed += 0x8000;
    }
}
