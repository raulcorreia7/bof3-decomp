#include "game_00.h"

MATCH void func_8019ACF4(void) {
    Actor* work;
    s32    pos;
    s32    step;

    func_8019AA44();
    work                = (Actor*)SCRATCH_WORK;
    pos                 = (g_AreaCameraOffsetZ << 16) + work->vy;
    /* FAKE: volatile re-read keeps the direction load before the store.
     */
    step                = FIELD(volatile s32, work, 0x10u);
    g_AreaCameraOffsetZ = (s16)(pos >> 16);
    if (step < 0) {
        if (g_AreaCameraOffsetZ < work->vx) {
            g_AreaCameraOffsetZ = (s16)work->vx;
        }
    } else {
        if (g_AreaCameraOffsetZ > work->vx) {
            g_AreaCameraOffsetZ = (s16)work->vx;
        }
    }
}
