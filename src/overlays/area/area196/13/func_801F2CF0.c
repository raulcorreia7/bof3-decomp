#include "area196_13.h"

MATCH void func_801F2CF0(void) {
    u8 timer;

    if (g_AreaSceneMode == 2) {
        TASK(Actor)->header.step += 1;
    }
    timer = TASK(Actor)->timer;
    if (timer < 32U) {
        TASK(Actor)->timer = timer + 1;
    }
    Game_SetCurrentActor(32 - TASK(Actor)->timer);
    TASK(Actor)->unk_0A += 1;
    TASK(Actor)->unk_0A &= 0x3F;
    func_801F3850();
}
