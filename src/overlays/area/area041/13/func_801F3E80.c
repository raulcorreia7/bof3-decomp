#include "area041_13.h"
#include "work/area_spad.h"

MATCH void func_801F3E80(void) {
    g_SpadWork->unk_0C = 0x4000;
    func_801F4118();
    g_SpadWork->unk_0A = 7;
    g_SpadWork->unk_04 = 1;
    g_GameState->unk_122 -= 2;
}
