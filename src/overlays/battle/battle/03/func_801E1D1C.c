#include "battle_03.h"

MATCH void func_801E1D1C(void) {
    if (EMI_LoaderIsReady() != 0) {
        Actor_RequestScript(g_SpadWork->word_08.byte.facing_08 + 0x24u);
        func_801DEE4C();
        g_SpadWork->unk_02 += 1;
    }
}
