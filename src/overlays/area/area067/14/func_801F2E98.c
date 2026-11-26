#include "area067_14.h"

MATCH void func_801F2E98(void) {
    Actor* actor;
    u16*   rect;
    u16    value;

    actor   = SELF(Actor);
    /* The quad a mode draws lives in the task's velocity words. */
    rect    = (u16*)&actor->vx;
    value   = rect[2] + 1;
    rect[2] = value;
    if ((s16)value > 0x40) {
        rect[2] = 0x40;
    }
    rect[3] += 0x40;
    func_801F358C(rect);
    if (--SELF(Actor)->timer == 0) {
        func_801F39AC();
        rect[4]            = 0;
        SELF(Actor)->timer = 0;
        SELF(Actor)->header.mode++;
    }
}
