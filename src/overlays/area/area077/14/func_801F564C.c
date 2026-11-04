#include "area077_14.h"

MATCH void func_801F564C(void) {
    ((Actor*)g_SpadWork)->unk_09 = 0;
    if (SYS_TestFlag(g_SceneEventFlags, 7)) {
        ((Actor*)g_SpadWork)->state_02 = 3;
    } else {
        func_801F529C(3, 0, 3, 3);
        ((Actor*)g_SpadWork)->state_02++;
    }
}
