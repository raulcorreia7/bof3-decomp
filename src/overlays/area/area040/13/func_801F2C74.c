#include "area040_13.h"

MATCH void func_801F2C74(void) {
    Actor* actor;

    if (g_GameState->slot_index_79 == 2) {
        actor          = g_SpadWork;
        actor->x.fixed = actor->x.fixed + 0x8000;
    }
}
