#include "area041_13.h"
#include "work/area_spad.h"

MATCH void func_801F3EE4(void) {
    func_801F4118();
    g_SpadWork->unk_0A -= 1;
    if (g_SpadWork->unk_0A == 0) {
        g_SpadWork->unk_0A = 8;
        g_SpadWork->unk_04 = 2;
    }
    g_GameState->unk_122 -= 2;
}
