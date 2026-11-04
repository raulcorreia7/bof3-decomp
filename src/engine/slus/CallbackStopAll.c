#include "engine/slus/slus.h"

/* closes every non-empty callback slot: each occupied slot is emptied and its
 * thread closed before a boot hand-over.
 */
MATCH void CallbackStopAll(void) {
    CallbackSlot*          slot_end;
    volatile CallbackSlot* next_slot;
    s32                    slot_index;

    slot_index     = 0;
    g_CallbackSlot = D_80143B40;
    slot_end       = D_80143B40 + 4;

    do {
        if (g_CallbackSlot->state != CALLBACK_SLOT_EMPTY) {
            CallbackCloseThread(slot_index & BYTE_MASK);
        }

        next_slot      = g_CallbackSlot + 1;
        g_CallbackSlot = (CallbackSlot*)next_slot;
    } while ((slot_index += 1, next_slot < slot_end));
}
