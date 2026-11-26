#include "game_00.h"

MATCH void func_801B0320(void) {
    Callback handler = D_801CD0E8[SELF(Actor)->header.step];
    handler();
    Script_AnimStepLoop();
}
