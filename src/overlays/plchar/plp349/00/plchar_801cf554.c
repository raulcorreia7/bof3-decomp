#include "plp349_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CF554(void) {
    g_Game.current->u.field.mode.value = 0;
}

MATCH void func_801CF564(void) {
    D_801CF62C[g_Task->unk_2C]();
}

MATCH void func_801CF5A8(void) {
    D_801CF638[g_Task->unk_2C]();
}
