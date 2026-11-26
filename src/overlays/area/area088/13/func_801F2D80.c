#include "area088_13.h"

MATCH void func_801F2D80(void) {
    u8 remaining;

    Trail_Update((Trail*)AREA_WORK);
    Trail_Draw(MEM_PTR(Trail, AREA_WORK));
    ACTOR_COUNT_DOWN(SELF(Actor), remaining, timer);
    if (!(remaining & BYTE_MASK)) {
        SELF(Actor)->timer = 16;
        SELF(Actor)->header.mode += 1;
    }
}
