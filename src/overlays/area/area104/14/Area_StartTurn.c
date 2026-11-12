#include "area104_14.h"

#ifdef NON_MATCHING
NON_MATCHING u8 Area_StartTurn(s32 direction, s32 previous) {
    Actor* work;
    s32    target;
    s32    heading;

    target  = direction;
    heading = previous;
    if (ABS((u8)target - (u8)heading) > 2) {
        if ((u8)target < (u8)heading) {
            target += 8;
        } else {
            heading += 8;
        }
        if (ABS((u8)target - (u8)heading) > 2) {
            return 0;
        }
    }
    if ((u8)target != (u8)heading) {
        work = g_Task;
        if ((u8)heading < (u8)target) {
            work->vz = -64;
            work->direction_08 -= 1;
        } else {
            work->vz = 64;
            work->direction_08 += 1;
        }
        g_Task->direction_08 &= 7;
        g_Game.members[0].facing = g_Task->direction_08;
        g_Task->timer            = 8;
        Area_UpdateTurn();
        g_Task->header.mode = 2;
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM(Area_StartTurn);
#endif
