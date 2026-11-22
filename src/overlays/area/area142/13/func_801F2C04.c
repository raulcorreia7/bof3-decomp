#include "area142_13.h"

MATCH s32 func_801F2C04(void) {
    SYS_DISPATCH_BYTE(D_801F3554, TASK(Actor)->header.step);
    func_801F2CB0(TASK(Actor)->timer);
}
