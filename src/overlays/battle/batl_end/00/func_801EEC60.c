#include "batl_end_00.h"

MATCH void func_801EEC60(void) {
    /* Retail takes the handler index from the entry $v0; the uninitialised local reads it. */
    u32 index;

    SYS_DISPATCH_INDEX(D_801F0C98, index);
}
