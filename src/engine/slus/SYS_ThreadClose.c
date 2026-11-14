#include "engine/slus/slus.h"

/* clears one callback slot and closes its thread inside the scheduler
 * critical section.
 */
MATCH void SYS_ThreadClose(s32 callback_slot) {
    D_80143B40[callback_slot].state = CALLBACK_SLOT_EMPTY;
    EnterCriticalSection();
    CloseTh(D_80143B40[callback_slot].thread_id);
    ExitCriticalSection();
}
