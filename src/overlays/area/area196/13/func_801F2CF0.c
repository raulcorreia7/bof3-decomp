#include "area196_13.h"

MATCH void func_801F2CF0(void) {
    u8 timer;

    if (g_AreaSceneMode == 2) {
        SELF(Actor)->header.step += 1;
    }
    timer = SELF(Actor)->timer;
    if (timer < 32U) {
        SELF(Actor)->timer = timer + 1;
    }
    Game_SetCurrentActor(32 - SELF(Actor)->timer);
    SELF(Actor)->unk_0A += 1;
    SELF(Actor)->unk_0A &= 0x3F;
    func_801F3850();
}
