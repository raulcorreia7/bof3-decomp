#include "area030_04.h"

/* Dispatches through the AREA030 state handler table selected by
 * slot 6's state index byte. */
MATCH void func_801DCC74(void) {
    D_801E22E4[g_SpawnedActors[6].unk_06]();
}
