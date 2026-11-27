#include "batl_ovr_00.h"

MATCH void func_801EEC0C(void) {
    /* Retail takes the handler index from the entry $v0; the uninitialised local reads it. */
    u32 index;

    SYS_DISPATCH_INDEX(D_801EF5F8, index);
}
