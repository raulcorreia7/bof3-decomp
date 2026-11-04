#include "area105_13.h"
#include "work/area_spad.h"

MATCH void func_801F2D38(void) {
    g_SpadWork->unk_09++;
    if (g_AreaSceneMode == 0) {
        Actor_Clear();
    }
    func_801F2D9C(g_SpadWork->unk_09);
}
