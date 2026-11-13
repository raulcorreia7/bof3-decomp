#include "area196_13.h"

MATCH void func_801F2CF0(void) {
    u8 timer;

    if (g_AreaSceneMode == 2) {
        g_Task->header.step += 1;
    }
    timer = g_Task->timer;
    if (timer < 32U) {
        g_Task->timer = timer + 1;
    }
    Game_SetCurrentActor(32 - g_Task->timer);
    g_Task->unk_0A += 1;
    g_Task->unk_0A &= 0x3F;
    func_801F3850();
}
