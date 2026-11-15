#include "game_00.h"

/* func_801B0DFC */
MATCH void Actor_UpdateMovement(void) {
    Actor_Move();
    if (g_Game.current->u.field.counter_11C.u8_value >= 4U) {
        Actor_StepAnimLoop();
    }
}
