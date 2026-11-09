#include "area030_04.h"

/* Dispatches the AREA030 scratchpad work byte 0x01 through the overlay's handler table. */
MATCH void func_801D0C98(void) {
    D_801E1CD4[FISHING_STATE->handler_index_01]();
}
