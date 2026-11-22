#include "area196_13.h"

MATCH void func_801F2DB0(void) {
    if (g_AreaSceneMode == 3) {
        TASK(Actor)->timer = 0;
        TASK(Actor)->header.step += 1;
    }
    Game_SetCurrentActor(0);
    TASK(Actor)->unk_0A = TASK(Actor)->unk_0A + 2;
    TASK(Actor)->unk_0A = TASK(Actor)->unk_0A & 0x3F;
    func_801F3850();
}
