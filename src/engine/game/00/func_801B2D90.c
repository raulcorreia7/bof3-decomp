#include "game_00.h"

MATCH void func_801B2D90(void) {
    Callback handler = D_801CD120[SELF(Actor)->header.step];

    handler();
    Script_AnimStepLoop();
}
