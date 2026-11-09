#include "engine/slus/slus.h"

/* re-arms the current callback slot with the callback `entry`: the
 * slot is marked open with that entry point, its thread is closed inside the
 * scheduler critical section, and the scheduler is forced to switch away from
 * the current callback.
 */
MATCH void CallbackReplace(Callback entry) {
    g_CallbackSlot->state    = CALLBACK_SLOT_OPEN;
    g_CallbackSlot->callback = entry;
    EnterCriticalSection();
    CloseTh(g_CallbackSlot->thread_id);
    ExitCriticalSection();
    ChangeTh(CALLBACK_FORCE_SWITCH);
}
