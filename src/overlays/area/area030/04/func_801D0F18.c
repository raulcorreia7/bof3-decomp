#include "area030_04.h"

/* Dispatches the AREA030 scratchpad work byte 0x03 through the overlay's handler table. */
MATCH void func_801D0F18(void) {
    D_801E1CF8[FISHING_STATE->sub_index_03]();
}
