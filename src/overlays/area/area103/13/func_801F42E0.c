#include "area103_13.h"

MATCH void func_801F42E0(void) {
    u8 frame = SELF(Actor)->timer;
    u8 stage = frame / 5;

    if (stage == 4) {
        Actor_Clear();
    } else {
        if (frame % 5 == 0) {
            func_801F4E70(7 - stage);
        }
        SELF(Actor)->timer++;
        func_801F49A0(1);
    }
}
