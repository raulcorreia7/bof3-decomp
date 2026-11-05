#include "game_00.h"

MATCH void Actor_Clear(void) {
    g_Task->flags = 0;
    g_Task->mode  = 0;
    ACTOR_CLEAR_STATE();
    g_Task->unk_03 = 0;
    g_Task->unk_04 = 0;
}
