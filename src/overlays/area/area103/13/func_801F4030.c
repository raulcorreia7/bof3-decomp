#include "area103_13.h"

MATCH void func_801F4030(void) {
    if (g_SpadWork->unk_09 % 5 == 0) {
        func_801F4E70(g_SpadWork->unk_09 / 5 + 4);
    }
    g_SpadWork->unk_09++;
    func_801F49A0(1);
    if (g_SpadWork->unk_09 / 5 == 3) {
        g_AreaSceneMode = 0;
        g_SpadWork->unk_09 = 1;
        g_SpadWork->state_02++;
    }
}
