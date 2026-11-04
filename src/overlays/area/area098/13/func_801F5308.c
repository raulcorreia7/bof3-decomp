#include "area098_13.h"

MATCH s32 func_801F5308(void) {
    MATRIX         camera;
    AreaSpawnSlot* slot;
    s32            active;
    u8             i;
    u8             life;

    active = 0;
    Area_SetCameraMatrix(&camera);
    slot = MEM_PTR(AreaSpawnSlot, AREA_WORK_WINDOW_ADDRESS);
    for (i = 0; i < 8; i++) {
        if (slot->active != 0) {
            active = 1;
            life   = slot->life_02 - 1;
            slot->unk_14 -= 0x10;
            slot->life_02 = life;
            if (life == 0) {
                slot->active = 0;
            }
            func_801F53BC(slot);
        }
        slot++;
    }
    return active;
}
