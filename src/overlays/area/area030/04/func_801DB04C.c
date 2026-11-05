#include "area030_04.h"

/* When the scratchpad work-object gate byte is set, selects the
 * character record stride 2 and latches the record's signed byte 0x07;
 * otherwise selects stride 1 and latches signed byte 0x04. */
MATCH void func_801DB04C(void) {
    if (FISHING_STATE->step_timer_09 != 0) {
        D_801E31F8 = 2;
        D_8014421C = D_801E320C->unk_07;
    } else {
        D_801E31F8 = 1;
        D_8014421C = D_801E320C->unk_04;
    }
}
