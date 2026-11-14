#include "engine/slus/slus.h"

/* clears bit 6 of the state word of thread_index.
 */
MATCH void func_8014B9D8(s32 thread_index) {
    g_SysThreads[thread_index].state &= ~0x40;
}
