#include "area149_13.h"

MATCH void func_801F2DAC(void) {
    u8* state;

    state  = &g_SceneState.step_05;
    *state = (*state + 1);
    Actor_Clear();
}
