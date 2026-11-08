#include "area120_13.h"

MATCH void func_801F2F84(void) {
    Actor* actor = g_Task;
    RECT   rect;

    actor->timer--;
    if (actor->timer == 0) {
        rect.x = 832;
        rect.y = 256;
        rect.w = D_801F43BC;
        rect.h = D_801F43BE;
        StoreImage(&rect, (u32*)AREA_WORK);
        g_Task->header.mode++;
    }
}
