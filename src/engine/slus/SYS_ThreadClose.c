#include "engine/slus/slus.h"

/* clears one thread and closes its OS thread inside the scheduler critical
 * section.
 */
MATCH void SYS_ThreadClose(s32 thread_index) {
    g_SysThreads[thread_index].state = SYS_THREAD_EMPTY;
    EnterCriticalSection();
    CloseTh(g_SysThreads[thread_index].thread_id);
    ExitCriticalSection();
}
