#include "area038_13.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

MATCH void func_801F2E60(void) {
    if (g_PartyFieldOrder[2] != 0) {
        return;
    }
    ACTOR_SEED_PARTY_SLOT(2, D_801F302C, 6, 3)
}
