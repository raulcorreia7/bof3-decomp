#include "area030_04.h"

/* Dispatches the AREA030 battle-intro scratchpad state byte through the overlay's jump table. */
/* func_801D20C8 */
MATCH void Fishing_LureRun(void) {
    g_FishingLureStates[FISHING_STATE->handler_index_01]();
}
