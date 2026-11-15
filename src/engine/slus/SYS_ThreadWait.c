#include "engine/slus/slus.h"

/*
 * arms the current thread with a countdown and forces one
 * scheduler switch through thread id `0xFF000000`.
 */

MATCH void SYS_ThreadWait(u16 countdown) {
    Thread* thread;

    thread            = g_SysCurrentThread;
    thread->countdown = countdown;
    thread->state     = SYS_THREAD_YIELD;
    ChangeTh(SYS_THREAD_FORCE_SWITCH);
}
