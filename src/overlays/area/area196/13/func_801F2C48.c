#include "area196_13.h"

MATCH void func_801F2C48(void) {
    SELF(Actor)->timer  = 0;
    SELF(Actor)->unk_0A = 0;
    SELF(Actor)->header.step += 1;
    Game_SetCurrentActor(0);
    func_801F3850();
}
