#include "engine/game/00/game_00.h"

/* func_801A2C10 */
/* Turns the current actor to a random odd facing. */
MATCH u8 Actor_TurnRandom(void* record) {
    u8  value;
    s16 next;

    value = SELF(Actor)->direction & 0x7;
    next  = (((s32 (*)(s32))rand)(0x80) & 0x7) | 0x1;
    if (value != next) {
        SELF(Actor)->direction = next;
        FIELD(u8, record, 0x74u) |= 8;
    }
    return SELF(Actor)->direction;
}
