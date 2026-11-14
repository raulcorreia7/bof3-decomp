#include "engine/slus/slus.h"

/*
 * stores one entry function in the thread at thread_index and marks it
 * open (state `2`).
 */
MATCH void SYS_ThreadRegister(s32 thread_index, Callback callback) {
    g_SysThreads[thread_index].entry = callback;
    g_SysThreads[thread_index].state = SYS_THREAD_OPEN;
}
