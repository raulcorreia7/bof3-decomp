#include "engine/slus/slus.h"

/* spins the shared tint step on the g_AreaCameraAngle.vz rotation cell until
 * the step reports completion, then clears the six tint bytes and releases the
 * callback thread.
 */
MATCH void func_8014F460(void) {
    s32  flag;
    u16* level;
    u16  value;

    flag  = 2;
    level = (u16*)&g_AreaCameraAngle.vz;
    value = 0;

loop:
    if ((GFX_UpdateScreenFade(&value, 0x800, 1, 0, flag) & BYTE_MASK) == 0) {
        *level = (*level + 0x20) & ANGLE_MASK;
        SYS_ThreadWait(1);
        /* Retail keeps this spin as a goto loop (as in GFX_RunWhiteFade). */
        goto loop;
    }

    D_80143E07 = 0;
    D_80143E06 = 0;
    D_80143E05 = 0;
    D_80143D77 = 0;
    D_80143D76 = 0;
    D_80143D75 = 0;
    SYS_ThreadExit();
}
