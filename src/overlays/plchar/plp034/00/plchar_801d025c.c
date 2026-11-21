#include "plp034_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801D025C(void) {
    g_Game.current->u.field.mode.value = 0;
}

MATCH void func_801D026C(void) {
    D_801D034C[g_Task->unk_2C]();
}

MATCH void func_801D02B0(void) {
    D_801D0358[g_Task->unk_2C]();
}
