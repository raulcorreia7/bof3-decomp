#include "logo/logo.h"

/* HAND_ASM: an `addi` overflow trap on the size and a branch into the next function, func_801D7568;
 * C89 has neither. */
#ifdef NON_MATCHING
/* for a size above 1, stores twice the size into the word at D_801D7544; returns the old word.
 * A size of 1 or less continues in func_801D7568, which the model leaves out. */
HAND_ASM int DecDCTvlcSize(int size) {
    u32* word;
    u32  old;

    word = (u32*)D_801D7544;
    old  = *word;
    if (size > 1) {
        *word = size * 2;
    }
    return old;
}
#else
INCLUDE_ASM(DecDCTvlcSize);
#endif
