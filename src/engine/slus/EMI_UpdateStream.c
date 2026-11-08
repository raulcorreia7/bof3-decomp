#include "engine/slus/slus.h"

/* Once per frame while an archive streams: runs the handler of each sector parked in the ring, marks the
 * archive ready when the ring is empty after the pause, and restarts a read that made no progress for
 * EMI_STREAM_TIMEOUT_FRAMES frames.
 */
MATCH void EMI_UpdateStream(void) {
    SystemDispatchFuncs callbacks;
    u8*                 head;
    s8*                 slot;
    s8                  next;
    s32                 count;
    u16*                frame_counter;

    head      = (u8*)&g_EmiReadStatus;
    callbacks = g_EmiRingSlotHandlers;
    if (*head != 0) {
        g_EmiStreamState = 0;
        EMI_StartArchive();
    }
    /* FAKE: the scheduler sinks the zeroing past the call; hold it in the
     * call's delay slot, where retail keeps the move. */
    FAKE_ORDER_LOCK(count = 0);
    EMI_CdUpdate();
    if ((g_EmiRingStates[D_80146488] & 0x80) == 0) {
        slot = (s8*)(head + 8);
        do {
            ((Callback)callbacks.handlers[g_EmiRingStates[*slot] & 0x7F])();
            g_EmiRingStates[*slot] = 0xFF;
            next                   = *slot + 1;
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
    frame_counter = &g_EmiStreamIdleFrames;
    if ((s16)(*frame_counter)++ >= EMI_STREAM_TIMEOUT_FRAMES) {
        if (g_EmiStreamState == 1) {
            EMI_StartArchive();
        }
    }
    if (g_EmiReadStatus != 0) {
        g_EmiStreamState = 0;
        EMI_StartArchive();
    }
}
