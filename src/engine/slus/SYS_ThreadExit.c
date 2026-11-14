#include "engine/slus/slus.h"

/*
 * clears the current slot state, closes its thread inside the
 * scheduler critical section, then forces a scheduler switch away from the
 * current callback.
 */
MATCH void SYS_ThreadExit(void) {
    g_CallbackSlot->state = CALLBACK_SLOT_EMPTY;
    EnterCriticalSection();
    CloseTh(g_CallbackSlot->thread_id);
    ExitCriticalSection();
    ChangeTh(SYS_THREAD_FORCE_SWITCH);
}
