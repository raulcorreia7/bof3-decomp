#include "engine/game/00/game_00.h"

/* func_8019CFCC */
/* Spins the shards and puffs of a broken block until the timer ends, then clears the actor. */
MATCH void Actor_BlockShatter(void) {
    u8 value;

    ACTOR_COUNT_DOWN(SELF(Actor), value, timer);
    if ((value & BYTE_MASK) == 0) {
        if (LOHU(g_GameAreaId) == AREA_ID_CONTAINER_YARD) {
            SYS_SetFlag(g_SceneEventFlags, 68);
        }
        Actor_Clear();
        return;
    }
    Actor_ShatterSpinShards();
    Actor_ShatterRunDust();
    Actor_ProjectForDraw();
}
