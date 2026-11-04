#include "area098_13.h"

MATCH void func_801F526C(void) {
    AreaSpawnSlot* slot;
    u8             i;

    slot = MEM_PTR(AreaSpawnSlot, AREA_WORK_WINDOW_ADDRESS);
    for (i = 0; i < 8; i++) {
        if (slot->active == 0) {
            slot->active = 1;
            slot->unk_01 = 0;
            slot->unk_02 = 0x10;
            slot->x      = g_SpadWork->x;
            slot->y      = g_SpadWork->y;
            slot->z      = g_SpadWork->z;
            slot->unk_14 = 0x100;
            slot->unk_16 = 0x40;
            slot->unk_17 = 0;
            return;
        }
        slot++;
    }
}
