#include "engine/slus/slus.h"

/* Sets SYS_THREAD_SUSPENDED in the state of thread thread_index, which SYS_ThreadRun then skips. */
MATCH void SYS_ThreadSuspend(s32 thread_index) {
    g_SysThreads[thread_index].state |= SYS_THREAD_SUSPENDED;
}
