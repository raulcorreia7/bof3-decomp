#include "battle_03.h"

MATCH void func_801E1D1C(void) {
    if (EMI_LoaderIsReady() != 0) {
        Actor_RequestScript(g_Task->facing + 0x24u);
        func_801DEE4C();
        g_Task->header.step += 1;
    }
}
