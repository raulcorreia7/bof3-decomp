#include "area030_04.h"

/* Steps the fishing sub-index while slot 6's mode is 3. */
MATCH void func_801DC904(void) {
    if (g_SpawnedActors[6].header.mode == 3) {
        TASK(FishingState)->sub_index++;
    }
}
