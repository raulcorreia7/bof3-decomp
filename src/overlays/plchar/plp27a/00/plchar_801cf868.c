#include "plp27a_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CF868(void) {
    g_Game.current->u.field.mode.value = 0;
}

MATCH void func_801CF878(void) {
    D_801CF92C[g_Task->unk_2C]();
}

MATCH void func_801CF8BC(void) {
    D_801CF938[g_Task->unk_2C]();
}
