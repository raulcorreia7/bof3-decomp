#include "area082_13.h"

MATCH void func_801F51BC(void) {
    D_8014933A = 0;
    Area_DrawGradient(0x10001805);
    TASK(Actor)->screen_y -= 6;
    TASK(Actor)->unk_32 = (TASK(Actor)->unk_32 - (TASK(Actor)->vz / 10000)) & 0xFFD;
    func_801F4430();
    TASK(Actor)->timer += 1;
    if (TASK(Actor)->timer >= 16U) {
        TASK(Actor)->header.step += 1;
    }
}
