#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F72A0(void) {
    /* Retail takes the handler index from the entry $v0; the uninitialised local reads it. */
    u32 index;

    /* FAKE: without the block the scheduler hoists the index shift above the
       ra store (84.46%); the lock restores the retail order (99.85%). */
    FAKE_ORDER_LOCK(D_801FE3D8[index]());
}

MATCH void func_801F72D4(void) {
    func_801FD29C();
    D_80146872 = 1;
}

INCLUDE_ASM(func_801F7300);

MATCH void func_801F7A00(void) {
    SYS_DISPATCH_BYTE(D_801FE3E4, g_SceneState.state_04);
}

MATCH void func_801F7A3C(void) {
}
