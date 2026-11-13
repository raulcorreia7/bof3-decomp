#include "area092_13.h"
#include "overlays/area/Actor_SeedPartySlot.h"

/* Give the first party member a field actor: claim a free slot and seed its row from the member. */
MATCH void func_801F304C(void) {
    ACTOR_SEED_PARTY_SLOT(0, D_801F3A88, 3)
}
