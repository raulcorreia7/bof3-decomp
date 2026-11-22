#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9FC4(void) {
    g_ScratchPad.cells.halves[0] = Actor_FindFreeField();
    if (g_ScratchPad.cells.halves[0] != 255) {
        Actor_SpawnFromRecord(D_801FE938);
    }
}
