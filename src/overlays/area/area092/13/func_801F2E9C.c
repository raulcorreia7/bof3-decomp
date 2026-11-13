#include "area092_13.h"
#include "overlays/area/Actor_SeedPartySlot.h"

/* Give the first party member a field actor: claim a free slot and seed its row from the member. */
MATCH void func_801F2E9C(void) {
    ACTOR_SEED_PARTY_SLOT(0, D_801F41C8, 4)
}
