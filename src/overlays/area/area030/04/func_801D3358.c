#include "area030_04.h"

/* Dispatches the AREA030 scratchpad state byte through the overlay's jump table. */
MATCH void func_801D3358(void) {
    D_801E1D8C[g_Task->header.mode]();
}
