#include "engine/slus/slus.h"

/* Clears SYS_THREAD_SUSPENDED in the state of thread thread_index. */
MATCH void SYS_ThreadResume(s32 thread_index) {
    g_SysThreads[thread_index].state &= ~SYS_THREAD_SUSPENDED;
}
