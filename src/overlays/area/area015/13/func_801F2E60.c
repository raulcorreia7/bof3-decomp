#include "area015_13.h"

MATCH void func_801F2E60(void) {
    if (SELF(Actor)->unk_0A-- == 0) {
        SELF(Actor)->unk_04 = 0;
    }
    if (g_ScenarioState.timer_06 == 0) {
        SELF(Actor)->unk_04 = 0;
        SELF(Actor)->unk_0A = 0;
    } else {
        g_ScriptState->cursor -= 2;
    }
}
