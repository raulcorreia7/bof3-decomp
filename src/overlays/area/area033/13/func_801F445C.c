#include "area033_13.h"

MATCH void func_801F445C(void) {
    u8* scratch;
    u8* work;

    scratch = (u8*)g_Task;
    if (scratch[0x0B] != 0) {
        if ((scratch[0] & ACTOR_FLAG_OFFSCREEN) != 0) {
            Actor_Clear();
            return;
        }
    } else if ((scratch[0] & ACTOR_FLAG_OFFSCREEN) == 0) {
        scratch[0x0B] = 1;
    }

    work = (u8*)g_Task;
    *(s32*)(work + 0x34) += *(s32*)(work + 0x0C);
    *(s32*)(work + 0x38) += *(s32*)(work + 0x10);
    Actor_StepAnimLoop();
    func_8014D290();
}
