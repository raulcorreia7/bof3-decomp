#include "engine/slus/slus.h"

/*
 * arms the current callback slot with a countdown and forces one
 * scheduler switch through thread id `0xFF000000`.
 */

MATCH void SYS_ThreadWait(u16 countdown) {
    Thread* slot;

    slot            = g_CallbackSlot;
    slot->countdown = countdown;
    slot->state     = CALLBACK_SLOT_YIELD;
    ChangeTh(SYS_THREAD_FORCE_SWITCH);
}
