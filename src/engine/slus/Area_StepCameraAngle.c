#include "engine/slus/slus.h"

/* lifted draft, best score 53.64%; semantics unverified
 */
/* nonmatching unmeasured: tried the first draft cleaned to compiling C; register pins dropped, score is the pinned draft; best
 * score 53.64%. resume: a lever or header fix that closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING s32 Area_StepCameraAngle(s32 degrees, s8 duration) {
    s32 tmp0;
    s32 tmp1;
    s32 val0;
    s32 val1;
    u8  tmp2;

    val0 = 4;
    tmp2 = g_RouteSpeedScale[D_80143FC0];
    if (D_801481F4 == 0) {
        if (tmp2 != 0) {
            val0 = 4;
            if (D_80143F50 != 2 && D_80143F50 != 6)
                val0 = 8;
            val1       = val0 * tmp2;
            tmp0       = duration * (0x80 / (s32)(val1 & BYTE_MASK));
            D_801481F0 = g_AreaCameraAngle.vz << 0x10;
            D_801481F4 = tmp0;
            D_80148200 = (s32)((((((degrees << 16) >> 4) / 360) - (g_AreaCameraAngle.vz & 0x7FF))) << 0x10) / tmp0;
        } else {
            g_AreaCameraAngle.vz = ((degrees << 16) >> 4) / 360;
        }
    } else {
        D_801481F4 -= 1;
        tmp1                 = D_801481F0 + D_80148200;
        D_801481F0           = tmp1;
        g_AreaCameraAngle.vz = (s16)(tmp1 >> 0x10);
    }
    return D_801481F4 != 0;
}
#else
INCLUDE_ASM(Area_StepCameraAngle);
#endif
