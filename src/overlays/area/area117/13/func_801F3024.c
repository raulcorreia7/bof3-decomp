#include "area117_13.h"

MATCH void func_801F3024(void) {
    u16 temp_v0;

    temp_v0 = ((Actor *)g_SpadWork)->unk_30 + 0x20;
    ((Actor *)g_SpadWork)->unk_30 = temp_v0;
    if ((s16)temp_v0 >= 0) {
        func_801F2E08();
        if (((Actor *)g_SpadWork)->state_02 != 2) {
            ((Actor *)g_SpadWork)->state_02 = 1;
            if (g_GameStateIndex == 0) {
                SND_PlayCue(0x201U);
            }
            goto block_4;
        }
    } else {
block_4:
        func_801F314C();
    }
}
