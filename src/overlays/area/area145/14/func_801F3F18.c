#include "area145_14.h"

MATCH void func_801F3F18(void) {
    s16 result;

    g_Task->vz += g_Task->gravity;
    func_801B0DFC();
    result = Area_ReadHeight(g_Task->x.fixed, g_Task->y.fixed);
    if (COORD_INT(g_Task->z) < result) {
        COORD_INT(g_Task->z) = result;
        g_Task->vz             = 0;
        g_Task->gravity        = 0;
        g_Task->unk_04         = 2;
        Actor_SelectScript(0x39U);
        g_ScriptState->unk_01 = 4;
        return;
    }
    g_ScriptState->cursor -= 2;
}
