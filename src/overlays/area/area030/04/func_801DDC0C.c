#include "area030_04.h"

/* When flag `D_80144125` is clear, calls `UI_SetMode` with 0 and increments byte 0x03 of the scratchpad work object. */
MATCH void func_801DDC0C(void) {
    if (D_80144125 == 0) {
        UI_SetMode(0);
        g_Task->unk_03 += 1;
    }
}
