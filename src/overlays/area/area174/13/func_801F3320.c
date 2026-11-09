#include "area174_13.h"

MATCH u16 func_801F3320(s32* from, s32* to) {
    DVECTOR start;
    DVECTOR end;

    Area_ProjectPoint(from, &start);
    Area_ProjectPoint(to, &end);
    return ratan2(end.vy - start.vy, end.vx - start.vx);
}
