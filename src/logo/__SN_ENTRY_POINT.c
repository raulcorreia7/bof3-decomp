#include "logo/logo.h"

/* HAND_ASM: the C runtime entry runs with no frame, sets `$gp` and tail-jumps to Logo_Main;
 * C89 cannot set `$gp` or end a function in a frameless jump. */
#if HAND_ASM_MODEL
/* clears the BSS words from jtbl_801EB430 up to D_801ECEC0, then runs the logo player. */
HAND_ASM void __SN_ENTRY_POINT(void) {
    u32* word;

    word = &jtbl_801EB430;
    do {
        *word++ = 0;
    } while (word < &D_801ECEC0);
    Logo_Main();
}
#else
INCLUDE_ASM(__SN_ENTRY_POINT);
#endif
