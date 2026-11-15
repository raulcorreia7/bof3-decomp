#include "area030_04.h"

/* Dispatches the AREA030 scratchpad state byte through the overlay's
 * jump table. */
/* func_801D42A0 */
MATCH void Fishing_CatchPageRun(void) {
    g_FishingStates[FISHING_STATE->handler_index_01]();
}
