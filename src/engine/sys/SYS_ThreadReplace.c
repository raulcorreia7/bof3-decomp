#include "engine/slus/slus.h"

/* re-arms the current thread with the entry `entry`: the thread is marked
 * open with that entry point, its OS thread is closed inside the scheduler
 * critical section, and the scheduler is forced to switch away from it.
 */
MATCH void SYS_ThreadReplace(Callback entry) {
    g_SysCurrentThread->state = SYS_THREAD_OPEN;
    g_SysCurrentThread->entry = entry;
    EnterCriticalSection();
    CloseTh(g_SysCurrentThread->thread_id);
    ExitCriticalSection();
    ChangeTh(SYS_THREAD_FORCE_SWITCH);
}
