#include "area108_14.h"

MATCH void func_801F4298(void) {
    u8* flags;
    u8  flag;

    MESSAGE_REQUEST_CLEAR();
    if (D_801490C7 == 0) {
        goto block_3;
    }
    if (D_801490C7 == 1) {
        goto block_4;
    }
    return;
block_3:
    flags  = &g_SaveData.scene_event.selection;
    *flags = 3;
    flags += 0x63B;
    flag = 0x1E;
    goto block_5;
block_4:
    flags  = &g_SaveData.scene_event.selection;
    *flags = 2;
    flags += 0x63B;
    flag = 0x1F;
block_5:
    SYS_SetFlag(flags, flag);
    g_SaveData.scene_event.mode = 5;
}
