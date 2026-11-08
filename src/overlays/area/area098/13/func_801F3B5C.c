#include "area098_13.h"

MATCH void func_801F3B5C(void) {
    u8 count;

    count          = g_Task->unk_06;
    g_Task->unk_06 = count + 1;
    if ((count & 3) == 0) {
        Area_ClaimSpawnSlot();
    }
    func_801F5940();
    Area_UpdateSpawnSlots();
    g_Task->timer = 0x20;
    g_Task->header.mode += 1;
}
