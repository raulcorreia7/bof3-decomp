#include "area120_13.h"

MATCH void func_801F2F84(void) {
    Actor* actor = SELF(Actor);
    RECT   rect;

    actor->timer--;
    if (actor->timer == 0) {
        setRECT(&rect, 832, 256, AREA120_IMAGE_RECT->box.w, AREA120_IMAGE_RECT->box.h);
        StoreImage(&rect, (u32*)AREA_WORK);
        SELF(Actor)->header.mode++;
    }
}
