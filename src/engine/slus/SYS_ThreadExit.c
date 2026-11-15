#include "engine/slus/slus.h"

/*
 * clears the current thread's state, closes the thread inside the
 * scheduler critical section, then forces a scheduler switch away from it.
 */
MATCH void SYS_ThreadExit(void) {
    g_SysCurrentThread->state = SYS_THREAD_EMPTY;
    EnterCriticalSection();
    CloseTh(g_SysCurrentThread->thread_id);
    ExitCriticalSection();
    ChangeTh(SYS_THREAD_FORCE_SWITCH);
}
