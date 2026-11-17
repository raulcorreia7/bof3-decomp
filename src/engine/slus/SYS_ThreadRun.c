#include "engine/slus/slus.h"

/*
 * initializes the current thread to the thread table, then walks all
 * four threads once: opens threads marked open, counts down yield
 * timers, and switches into any thread whose timer expired or that requested
 * a forced switch.
 */
MATCH void SYS_ThreadRun(void) {
    g_SysCurrentThread = g_SysThreads;
    {
        int idle_state = SYS_THREAD_IDLE;

        do {
            switch (g_SysCurrentThread->state) {
                case SYS_THREAD_OPEN:
                    EnterCriticalSection();
                    g_SysCurrentThread->thread_id = OpenTh((long (*)())g_SysCurrentThread->entry, g_SysCurrentThread->stack, g_SysCurrentThread->gp);
                    ExitCriticalSection();
                    goto dispatch; /* a freshly opened thread switches in at once, like a forced switch */

                case SYS_THREAD_YIELD:
                    if (--g_SysCurrentThread->countdown != 0) {
                        break;
                    }
                    /* fall through */

                case SYS_THREAD_SWITCH:
                dispatch:
                    g_SysCurrentThread->state = idle_state;
                    ChangeTh(g_SysCurrentThread->thread_id);
                    break;
            }

            g_SysCurrentThread++;
        } while (g_SysCurrentThread < (Thread*)&g_SysCurrentThread);
    }
}
