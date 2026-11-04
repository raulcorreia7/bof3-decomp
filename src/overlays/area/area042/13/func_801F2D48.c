#include "area042_13.h"

MATCH void func_801F2D48(void) {
    func_801F2E78(&g_SpadWork->unk_0C, &g_SpadWork->unk_18);
    func_801F2DC4();
    if (SYS_TestFlag(g_SceneEventFlags, 0xB) == 0) {
        g_SpadWork->unk_01 = 0;
    }
}
