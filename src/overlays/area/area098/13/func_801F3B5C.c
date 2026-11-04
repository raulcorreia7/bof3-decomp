#include "area098_13.h"

MATCH void func_801F3B5C(void) {
    u8 count;

    count              = g_SpadWork->unk_06;
    g_SpadWork->unk_06 = count + 1;
    if ((count & 3) == 0) {
        Area_ClaimSpawnSlot();
    }
    func_801F5940();
    func_801F5308();
    g_SpadWork->unk_09 = 0x20;
    g_SpadWork->unk_01 += 1;
}
