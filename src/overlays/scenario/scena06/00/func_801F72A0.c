#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F72A0(void) {
    /* Retail takes the handler index from the entry $v0; the uninitialised local reads it. */
    u32 index;

    SYS_DISPATCH_INDEX(D_801FE3D8, index);
}

MATCH void func_801F72D4(void) {
    func_801FD29C();
    D_80146872 = 1;
}
