#include "battle_03.h"

MATCH void func_801E75B0(void) {
    u32 slot;

    if (D_801EB4E0->unk_2C.half == 0) {
        slot = 0x23E;
        if (((u8*)D_801EB4E0)[8] < 2u) {
            slot = 0x23C;
        }
    } else {
        slot = 0x23F;
        if (((u8*)D_801EB4E0)[8] < 2u) {
            slot = 0x23D;
        }
    }
    EMI_LoaderStreamInitSlot(slot);
    g_Task->header.mode++;
}
