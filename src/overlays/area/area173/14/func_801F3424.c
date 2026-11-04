#include "area173_14.h"

MATCH void func_801F3424(void) {
    Actor* work;

    if (g_AreaSceneMode == 2) {
        SP_REF(s16, 0x38u) = 0;
        SP_REF(s16, 0x3Au) = 0;
        func_801F3954(0);
        func_801F3954(1);
        func_801F3954(2);
        SND_PlayCue(0x205);
        work = g_SpadWork;
        work->state_02++;
    }
}
