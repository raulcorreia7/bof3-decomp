#include "area030_04.h"

/* Dispatches the AREA030 scratchpad state byte through the overlay's jump table. */
MATCH void func_801D2978(void) {
    D_801E1D78[FISHING_STATE->handler_index_01]();
}
