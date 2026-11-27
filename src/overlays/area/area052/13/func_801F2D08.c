#include "area052_13.h"

MATCH void func_801F2D08(void) {
    SpawnedActor* slot;
    u8            i;

    slot = g_SpawnedActors;
    for (i = 0; i < ACTOR_SLOT_COUNT; i++) {
        if (slot->header.flags != 0 && slot->type == 0x48 && (void*)slot != (void*)g_Self) {
            Actor_Clear();
            return;
        }
        slot++;
    }
    SELF(Actor)->unk_06 = 0;
    SELF(Actor)->timer  = 0;
    func_801F3194();
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
    SELF(Actor)->header.mode++;
}
