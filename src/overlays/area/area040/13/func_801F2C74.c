#include "area040_13.h"

MATCH void func_801F2C74(void) {
    Actor* actor;

    if (g_GameState->chr.character_id == CHAR_ID_GARR) {
        actor = g_Task;
        actor->pos.x.fixed += COORD_HALF;
    }
}
