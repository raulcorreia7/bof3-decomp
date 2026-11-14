#include "engine/slus/slus.h"

/* HAND_ASM: PsyQ startup code that ends by falling through into stup1 with no epilogue;
 * C89 cannot emit a function with no return path. */
#ifdef NON_MATCHING
/* clears the BSS words from g_SysStartupReturn up to D_80190C60. */
HAND_ASM void stup2(void) {
    u32* word;

    word = &g_SysStartupReturn;
    do {
        *word++ = 0;
    } while (word < &D_80190C60);
}
#else
INCLUDE_ASM(stup2);
#endif
