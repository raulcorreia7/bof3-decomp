#include "boss025_13.h"

MATCH void func_800C1CB0(void) {
    Actor_RequestScript(0xF);
    g_SpadWork->unk_2A = 0;
    func_8014DAEC();
    func_801E54EC();
    g_SpadWork->flags_00 &= ~ACTOR_FLAG_HIDDEN;
    g_SpadWork->step_01 = 3;
    g_SpadWork->unk_02  = 0;
    g_SpadWork->unk_03  = 0;
}
