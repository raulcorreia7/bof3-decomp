#include "area098_13.h"

MATCH void func_801F2E98(void) {
    Actor* actor = SELF(Actor);
    RECT   rect;

    actor->timer--;
    if (actor->timer == 0) {
        setRECT(&rect, 832, 256, D_801F5F58[D_801F6520].w, D_801F5F58[D_801F6520].h);
        StoreImage(&rect, (u32*)AREA_WORK);
        SELF(Actor)->header.mode++;
    }
}
