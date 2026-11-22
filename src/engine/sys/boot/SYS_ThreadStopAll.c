#include "engine/slus/slus.h"

/* closes every non-empty thread: each occupied thread is emptied and its OS
 * thread closed before a boot hand-over.
 */
MATCH void SYS_ThreadStopAll(void) {
    Thread*          thread_end;
    volatile Thread* next_thread;
    s32              thread_index;

    thread_index       = 0;
    g_SysCurrentThread = g_SysThreads;
    thread_end         = g_SysThreads + SYS_THREAD_COUNT;

    do {
        if (g_SysCurrentThread->state != SYS_THREAD_EMPTY) {
            SYS_ThreadClose(thread_index & BYTE_MASK);
        }

        next_thread        = g_SysCurrentThread + 1;
        g_SysCurrentThread = (Thread*)next_thread;
    } while ((thread_index += 1, next_thread < thread_end));
}
