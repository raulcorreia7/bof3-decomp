#include "area048_13.h"

MATCH void func_801F37F4(void) {
    func_801F3AE4(0, 0x858000, 0);
    func_801F3AE4(0x800, 0x878000, 1);
    if (g_AreaSceneMode != 0) {
        g_SpadWork->state_02++;
        g_SpadWork->unk_09 = 0;
    }
}
