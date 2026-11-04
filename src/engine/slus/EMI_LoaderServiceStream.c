#include "engine/slus/slus.h"

/* runs pending slot handlers, advances the slot cursor, and
 * rearms the loader when the frame counter expires.
 */
MATCH void EMI_LoaderServiceStream(void) {
    SystemDispatchFuncs callbacks;
    u8*                 head;
    s8*                 slot;
    s8                  next;
    s32                 count;
    u16*                frame_counter;

    head      = (u8*)&g_EmiReadStatus;
    callbacks = g_EmiSlotDrainFuncs;
    if (*head != 0) {
        g_EmiStreamState = 0;
        EMI_LoaderBeginRead();
    }
    /* FAKE: the scheduler sinks the zeroing past the call; hold it in the
     * call's delay slot, where retail keeps the move. */
    ORDER_LOCK(count = 0);
    EMI_LoaderRunCd();
    if ((g_EmiRingStates[D_80146488] & 0x80) == 0) {
        slot = (s8*)(head + 8);
        do {
            ((Callback)callbacks.handlers[g_EmiRingStates[*slot] & 0x7F])();
            g_EmiRingStates[*slot] = 0xFF;
            next                   = (u8)*slot + 1;
            *slot                  = next;
            if (next == EMI_CALLBACK_SLOT_COUNT) {
                *slot = 1;
            }
            *(u16*)(slot + 8) = 0;
            count++;
        } while ((g_EmiRingStates[*slot] & 0x80) == 0);
    }
    if (count == 0) {
        u8* read_progress = &g_EmiStreamState;

        if (*read_progress == 2) {
            *read_progress   = 3;
            g_EmiStreamFlags = 0;
        }
    }
    frame_counter = &D_80146490;
    if ((s16)(*frame_counter)++ >= 0x12D) {
        if (g_EmiStreamState == 1) {
            EMI_LoaderBeginRead();
        }
    }
    if (g_EmiReadStatus != 0) {
        g_EmiStreamState = 0;
        EMI_LoaderBeginRead();
    }
}
