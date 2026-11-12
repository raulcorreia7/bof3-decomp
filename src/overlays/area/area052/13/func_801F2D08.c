#include "area052_13.h"

MATCH void func_801F2D08(void) {
    ActorSlot* slot;
    u8         i;

    slot = g_ActorSlots;
    for (i = 0; i < ACTOR_SLOT_COUNT; i++) {
        if (slot->header.flags != 0 && slot->type == 0x48 && (void*)slot != (void*)g_Task) {
            Actor_Clear();
            return;
        }
        slot++;
    }
    g_Task->unk_06 = 0;
    g_Task->timer  = 0;
    func_801F3194();
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
    g_Task->header.mode++;
}
