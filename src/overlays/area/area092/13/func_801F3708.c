#include "area092_13.h"
#include "overlays/area/Actor_SeedPartySlot.h"

/* Give the second party member a field actor: claim a free slot and seed its row from the member. */
MATCH void func_801F3708(void) {
    ACTOR_SEED_PARTY_SLOT(1, D_801F3A90, 1)
}
