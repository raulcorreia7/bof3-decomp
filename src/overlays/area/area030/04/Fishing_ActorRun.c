#include "area030_04.h"

/* Dispatches the AREA030 scratchpad state byte through the overlay's
 * jump table. */
/* func_801D2978 */
MATCH void Fishing_ActorRun(void) {
    D_801E1D78[FISHING_STATE->handler_index_01]();
}
