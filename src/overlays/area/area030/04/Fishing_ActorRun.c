#include "area030_04.h"

/* Dispatches the AREA030 scratchpad state byte through the overlay's
 * jump table. */
/* func_801D2978 */
MATCH void Fishing_ActorRun(void) {
    g_FishingActorRunHandlers[SELF(FishingState)->handler_index]();
}
