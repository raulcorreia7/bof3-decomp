#include "engine/slus/slus.h"

/*
 * initializes the callback cursor to the slot table, then walks all
 * four slots once: opens threads for slots marked open, counts down yield
 * timers, and switches into any slot whose timer expired or that requested a
 * forced switch.
 */
MATCH void CallbackRun(void) {
    g_CallbackSlot = D_80143B40;
    {
        int idle_state = CALLBACK_SLOT_IDLE;

        do {
            switch (g_CallbackSlot->state) {
                case CALLBACK_SLOT_OPEN:
                    EnterCriticalSection();
                    g_CallbackSlot->thread_id = OpenTh((long (*)())g_CallbackSlot->callback, g_CallbackSlot->open_arg,
                                                       g_CallbackSlot->open_arg_2);
                    ExitCriticalSection();
                    goto dispatch; /* a freshly opened slot switches in at once, like a forced switch */

                case CALLBACK_SLOT_YIELD:
                    if (--g_CallbackSlot->countdown != 0) {
                        break;
                    }
                    /* fall through */

                case CALLBACK_SLOT_SWITCH:
                dispatch:
                    g_CallbackSlot->state = idle_state;
                    ChangeTh(g_CallbackSlot->thread_id);
                    break;
            }

            g_CallbackSlot++;
        } while (g_CallbackSlot < (CallbackSlot*)&g_CallbackSlot);
    }
}
