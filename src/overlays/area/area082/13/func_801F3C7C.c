#include "area082_13.h"

MATCH void func_801F3C7C(void) {
    SELF(Actor)->timer += 1;
    if (SELF(Actor)->timer >= 17U) {
        SELF(Actor)->timer        = 0;
        SELF(Actor)->param.unk_0B = 1;
        SELF(Actor)->header.step += 1;
    }
    func_801F4430();
}
