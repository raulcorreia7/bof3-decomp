#include "game_00.h"

MATCH void func_801B830C(void) {
    u8 step;

    if (g_Task->timer == 0) {
        step           = g_Task->unk_0A + 1;
        g_Task->unk_0A = step;
        if (step == 3) {
            g_GameStateIndex = GAME_REQUEST_AREA_CHANGE;
        }
        func_801C24D0();
    }
    g_Task->timer = g_Task->timer - 1;
    Actor_UpdateMovement();
    Actor_StepAnimLoop();
}
