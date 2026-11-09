#include "engine/slus/slus.h"

/* clears the current slot state, closes its thread inside the scheduler critical section. */
MATCH void CallbackExit(void) {
    g_CallbackSlot->state = CALLBACK_SLOT_EMPTY;
    EnterCriticalSection();
    CloseTh(g_CallbackSlot->thread_id);
    ExitCriticalSection();
    ChangeTh(CALLBACK_FORCE_SWITCH);
}
