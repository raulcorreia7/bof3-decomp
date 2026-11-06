#include "start_08.h"

/* Prompt row/column state bytes and the prompt draw helper. */

MATCH void func_801E6D88(s32 prompt_x) {
    if (D_801ED86C != 0) {
        prompt_x &= BYTE_MASK;
        func_801E6E18(0x60, 0x50, 0, D_801ED864, prompt_x);
        func_801E6E18(0x5C, 0x70, 1, D_801ED868, prompt_x);
    } else {
        func_801E6E18(0x60, 0x60, 0, D_801ED864, prompt_x & BYTE_MASK);
    }
}
