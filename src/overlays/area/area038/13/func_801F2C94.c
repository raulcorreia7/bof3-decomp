#include "area038_13.h"
#include "overlays/area/Actor_SeedPartySlot.h"

MATCH void func_801F2C94(void) {
    if (g_PartyFieldOrder[1] != 0) {
        return;
    }
    ACTOR_SEED_PARTY_SLOT(1, D_801F302C, 6, 3)
}
