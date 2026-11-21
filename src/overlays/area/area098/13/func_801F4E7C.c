#include "area098_13.h"

MATCH s32 func_801F4E7C(void) {
    u8            i;
    s32           live;
    FallingSpark* slot;
    u8            buffer[32];

    live = 0;
    GFX_AddDitheredDrawMode(2, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y));
    Camera_SetMatrix(buffer);
    slot = MEM_PTR(FallingSpark, AREA_WORK);
    for (i = 0; i < 16; i += 1, slot++) {
        if (slot->header.active != 0) {
            D_801F5FBC[slot->header.type](slot);
            live = 1;
            func_801F4BC0(slot);
        }
    }
    return live;
}
