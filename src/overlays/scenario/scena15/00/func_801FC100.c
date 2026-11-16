#include "scena15_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FC100(void) {
    u8 i;

    for (i = 0; i < 3; i++) {
        D_1F800000.cells.halves[0] = Actor_FindFreeField();
        if (D_1F800000.cells.halves[0] != GAME_NONE) {
            func_801A4D54(&D_801FE694[i * 17]);
        }
    }
    for (i = 0; i < 2; i++) {
        D_1F800000.cells.halves[0] = Actor_FindFreeField();
        if (D_1F800000.cells.halves[0] != GAME_NONE) {
            func_801A65A0(&D_801FE6C8[i * 16]);
        }
    }
}
