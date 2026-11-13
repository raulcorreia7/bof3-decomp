#include "area196_13.h"

MATCH void func_801F2C48(void) {
    g_Task->timer  = 0;
    g_Task->unk_0A = 0;
    g_Task->header.step += 1;
    Game_SetCurrentActor(0);
    func_801F3850();
}
