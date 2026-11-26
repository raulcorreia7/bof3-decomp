#include "area172_13.h"

MATCH void func_801F32E8(void) {
    u8 phase = SELF(Actor)->unk_06;

    SELF(Actor)->unk_06 = phase + 1;
    if ((phase & 0x3) == 0) {
        Area_ClaimSpawnSlot();
    }
    func_801F3FAC();
    Area_UpdateSpawnSlots();
    if (g_SysThreads[2].state == 0) {
        UI_ModeSet(9);
        g_AreaDrawFlags = 0;
        SELF(Actor)->header.mode++;
    }
}
