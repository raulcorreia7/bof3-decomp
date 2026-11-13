#include "area192_13.h"

MATCH void func_801F3444(void) {
    u8* flags;
    u8  fatigue;
    u8  mode;
    u8  i;
    s16 slot;

    /* The flag rows lie in the save block above the record; retail reaches them from its base. */
    flags   = &g_Characters[0].fatigue;
    fatigue = flags[0];
    if (SYS_TestFlag(flags + 0x5A6, 0x77) != 0) {
        return;
    }
    if (!SYS_TestFlag(flags + 0x576, 0xA)) {
        if (fatigue < 9) {
            if (fatigue < 5) {
                mode = D_80144F56 >= 5;
            } else {
                mode = 1;
            }
        } else {
            mode = 2;
        }
    } else if (fatigue < 5) {
        mode = D_80144F56 >= 5;
    } else {
        mode = 2;
    }
    for (i = 0; i < 6; i++) {
        slot                                = Actor_FindFree();
        D_1F800000.view.area.entity_counter = slot;
        if (slot != GAME_NONE) {
            func_801A4D54(D_801F3A08[mode] + i * 17);
        }
    }
}
