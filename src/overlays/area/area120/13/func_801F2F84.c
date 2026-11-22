#include "area120_13.h"

MATCH void func_801F2F84(void) {
    Actor* actor = TASK(Actor);
    RECT   rect;

    actor->timer--;
    if (actor->timer == 0) {
        setRECT(&rect, 832, 256, D_801F43BC, D_801F43BE);
        StoreImage(&rect, (u32*)AREA_WORK);
        TASK(Actor)->header.mode++;
    }
}
