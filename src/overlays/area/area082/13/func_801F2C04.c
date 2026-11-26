#include "area082_13.h"

MATCH s32 func_801F2C04(void) {
    SYS_DISPATCH_BYTE(D_801F5734, SELF(Actor)->header.mode);
    if (SELF(Actor)->header.mode != 0) {
        func_801F3264();
    }
}
