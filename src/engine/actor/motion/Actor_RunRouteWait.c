#include "engine/game/00/game_00.h"

/* func_801A271C */
/* Mode 5: counts down the wait the route script set, then returns to the saved mode. */
MATCH void Actor_RunRouteWait(void* record) {
    u8 timer;

    timer = FIELD(u8, record, 0x75u);
    if (timer == 0) {
        SELF(Actor)->header.mode = SELF(Actor)->unk_03;
        return;
    }
    FIELD(u8, record, 0x75u) = timer - 1;
    FIELD(u8, record, 0x74u) |= 0x10;
}
