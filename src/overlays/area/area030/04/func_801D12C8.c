#include "area030_04.h"

/* Dispatches the AREA030 scratchpad mode byte through the overlay's jump table. */
MATCH void func_801D12C8(void) {
    D_801E1D00[FISHING_STATE->sub_index_03]();
}
