#include "area082_13.h"

MATCH void func_801F3D04(void) {
    TASK(Actor)->timer += 1;
    if (TASK(Actor)->timer >= 17U) {
        TASK(Actor)->timer        = 0;
        TASK(Actor)->param.unk_0B = 2;
        TASK(Actor)->header.step += 1;
    }
    func_801F4430();
}
