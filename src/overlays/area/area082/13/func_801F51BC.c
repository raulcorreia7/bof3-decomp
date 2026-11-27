#include "area082_13.h"

MATCH void func_801F51BC(void) {
    D_8014933A = 0;
    Area_DrawGradient(0x10001805);
    SELF(Actor)->screen_y -= 6;
    SELF(Actor)->unk_32 = (SELF(Actor)->unk_32 - (SELF(Actor)->vz / 10000)) & 0xFFD;
    func_801F4430();
    SELF(Actor)->timer += 1;
    if (SELF(Actor)->timer >= 16U) {
        SELF(Actor)->header.step += 1;
    }
}
