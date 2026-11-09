#include "engine/slus/slus.h"

/* re-arms the current callback slot with the callback `entry`. */
MATCH void CallbackReplace(Callback entry) {
    g_CallbackSlot->state    = CALLBACK_SLOT_OPEN;
    g_CallbackSlot->callback = entry;
    EnterCriticalSection();
    CloseTh(g_CallbackSlot->thread_id);
    ExitCriticalSection();
    ChangeTh(CALLBACK_FORCE_SWITCH);
}
