#include "battle_03.h"

MATCH void func_801D716C(void) {
    if (EMI_LoaderIsReady() != 0) {
        g_Battle.phase.step     = 4;
        g_Battle.phase.sub_step = 0;
    }
}
