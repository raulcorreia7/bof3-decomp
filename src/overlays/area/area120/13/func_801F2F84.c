#include "area120_13.h"

MATCH void func_801F2F84(void) {
    Actor* actor = g_SpadWork;
    RECT   rect;

    actor->unk_09--;
    if (actor->unk_09 == 0) {
        rect.x = 0x340;
        rect.y = 0x100;
        rect.w = D_801F43BC;
        rect.h = D_801F43BE;
        StoreImage(&rect, (u32*)AREA_WORK_WINDOW_ADDRESS);
        g_SpadWork->unk_01++;
    }
}
