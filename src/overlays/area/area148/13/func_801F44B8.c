#include "area148_13.h"

MATCH void func_801F44B8(void) {
    func_801F4798(&TASK(Actor)->pos.x, &TASK(Actor)->unk_18);
    func_801F4614();
    TASK(Actor)->unk_0A -= 1;
    if (TASK(Actor)->unk_0A == 0) {
        TASK(Actor)->timer += 1;
        TASK(Actor)->header.mode = 1;
    }
}
