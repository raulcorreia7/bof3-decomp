#include "area030_04.h"

/* Snapshots flag byte `D_801E31F0` into `D_801E31F4`, then sets
 * `D_801E31F0` from mask 0xE040 on halfword `g_InputPressed`: 1 when any masked
 * bit is set, 0 otherwise. */
MATCH void func_801DDFD4(void) {
    D_801E31F4 = D_801E31F0;
    if ((g_InputPressed & (PADRdown | PADLright | PADLdown | PADLleft)) != 0) {
        D_801E31F0 = 1;
    } else {
        D_801E31F0 = 0;
    }
}
