#include "area148_13.h"

MATCH void func_801F44B8(void) {
    func_801F4798(&SELF(Actor)->pos.x, &SELF(Actor)->unk_18);
    func_801F4614();
    SELF(Actor)->unk_0A -= 1;
    if (SELF(Actor)->unk_0A == 0) {
        SELF(Actor)->timer += 1;
        SELF(Actor)->header.mode = 1;
    }
}
