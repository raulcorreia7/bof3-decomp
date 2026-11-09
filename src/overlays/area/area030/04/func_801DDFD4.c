#include "area030_04.h"

/* Snapshots flag byte `D_801E31F0` into `D_801E31F4`. */
MATCH void func_801DDFD4(void) {
    D_801E31F4 = D_801E31F0;
    if ((g_InputPressed & (PADRdown | PADLright | PADLdown | PADLleft)) != 0) {
        D_801E31F0 = 1;
    } else {
        D_801E31F0 = 0;
    }
}
