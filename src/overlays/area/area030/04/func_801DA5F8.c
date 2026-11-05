#include "area030_04.h"

/* Increments the shared state byte at 0x801440B1, reports it through
 * func_8014D8D4 with argument 1, and sets byte 0x03 of the local-work block
 * selected by the non-volatile scratchpad pointer cell at 0x1F800044. */

MATCH void func_801DA5F8(void) {
    u8* state_byte = &D_801440B1;

    (*state_byte)++;
    Actor_RequestScript(1);
    TASK_BYTES[3] = 1;
}
