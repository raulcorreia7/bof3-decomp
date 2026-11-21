#include "engine/slus/slus.h"

/* HAND_ASM: the return-zero tail of libgte SquareRoot0, which branches here; no function of its own,
 * and GCC 2.7.2 writes `move $v0, $zero` for a zero return, not this `addiu`. */
#if HAND_ASM_MODEL
HAND_ASM s32 func_80178764(void) {
    return 0;
}
#else
INCLUDE_ASM(func_80178764);
#endif
