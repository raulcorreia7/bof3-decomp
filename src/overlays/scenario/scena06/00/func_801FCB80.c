#include "scena06_00.h"
#include "area/map.h"
#include "area/spad.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Give the lead party member a field actor of type 6: claim a free slot and seed its row from the member. */
MATCH void func_801FCB80(s32 variant) {
    ACTOR_SEED_PARTY_SLOT(0, D_801FE3BC, 6, variant + 112)
}
