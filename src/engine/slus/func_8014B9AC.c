#include "engine/slus/slus.h"

/* sets bit 6 of the state word of thread_index.
 */
MATCH void func_8014B9AC(s32 thread_index) {
    g_SysThreads[thread_index].state |= 0x40;
}
