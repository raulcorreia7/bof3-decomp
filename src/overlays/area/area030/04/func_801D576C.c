#include "area030_04.h"

/* Dispatches the AREA030 scratchpad state byte through the overlay's
 * jump table. */
MATCH void func_801D576C(void) {
    D_801E1FD4[FISHING_STATE->sub_index_03]();
}
