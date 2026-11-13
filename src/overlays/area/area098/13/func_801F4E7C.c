#include "area098_13.h"

MATCH s32 func_801F4E7C(void) {
    u8             i;
    s32            live;
    AreaBurstSlot* slot;
    u8             buffer[32];

    live = 0;
    GFX_AddDitheredDrawMode(2, GetTPage(0, 1, 0x3C0, 0));
    Area_SetCameraMatrix(buffer);
    slot = MEM_PTR(AreaBurstSlot, AREA_WORK);
    for (i = 0; i < 16; i += 1, slot++) {
        if (slot->active != 0) {
            D_801F5FBC[slot->kind](slot);
            live = 1;
            func_801F4BC0(slot);
        }
    }
    return live;
}
