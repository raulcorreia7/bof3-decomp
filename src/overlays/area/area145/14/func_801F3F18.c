#include "area145_14.h"

MATCH void func_801F3F18(void) {
    s16 result;

    g_SpadWork->vz += g_SpadWork->gravity;
    func_801B0DFC();
    result = Area_ReadHeight(g_SpadWork->x.fixed, g_SpadWork->y.fixed);
    if (g_SpadWork->z.part.integer < result) {
        g_SpadWork->z.part.integer = result;
        g_SpadWork->vz             = 0;
        g_SpadWork->gravity        = 0;
        g_SpadWork->unk_04         = 2;
        Actor_SelectScript(0x39U);
        g_ScriptState->unk_01 = 4;
        return;
    }
    g_ScriptState->cursor -= 2;
}
