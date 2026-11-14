#include "engine/slus/slus.h"

/* closes every non-empty callback slot: each occupied slot is emptied and its
 * thread closed before a boot hand-over.
 */
MATCH void SYS_ThreadStopAll(void) {
    Thread*          slot_end;
    volatile Thread* next_slot;
    s32              callback_slot;

    callback_slot  = 0;
    g_CallbackSlot = D_80143B40;
    slot_end       = D_80143B40 + 4;

    do {
        if (g_CallbackSlot->state != CALLBACK_SLOT_EMPTY) {
            SYS_ThreadClose(callback_slot & BYTE_MASK);
        }

        next_slot      = g_CallbackSlot + 1;
        g_CallbackSlot = (Thread*)next_slot;
    } while ((callback_slot += 1, next_slot < slot_end));
}
