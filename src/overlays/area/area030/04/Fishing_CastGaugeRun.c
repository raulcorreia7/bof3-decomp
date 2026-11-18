#include "area030_04.h"

/* Dispatches the AREA030 scratchpad state byte through the overlay's
 * jump table. */
/* func_801D1B10 */
MATCH void Fishing_CastGaugeRun(void) {
    g_FishingCastGaugeSteps[FISHING_STATE->handler_index]();
}
