#include "area134_13.h"

MATCH void func_801F4214(void) {
    s32 count;

    if (D_801F5818 == 0) {
        Area_ClearWorkColumn();
    }
    SELF(Actor)->timer  = 128;
    count               = D_801F5818 + 1;
    D_801F5818          = count;
    SELF(Actor)->unk_06 = count;
    SELF(Actor)->header.mode += 1;
}
