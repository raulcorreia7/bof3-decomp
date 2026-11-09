#include "area098_13.h"

MATCH void func_801F2E98(void) {
    Actor* actor = g_Task;
    RECT   rect;

    actor->timer--;
    if (actor->timer == 0) {
        rect.x = 832;
        rect.y = 256;
        rect.w = D_801F5F5C[D_801F6520].w;
        rect.h = D_801F5F5C[D_801F6520].h;
        StoreImage(&rect, (u32*)AREA_WORK);
        g_Task->header.mode++;
    }
}
