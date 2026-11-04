#include "engine/slus/slus.h"

/* services the active EMI CD-ready callback, validates the sector
 * source, dispatches the current loader phase, and advances the streaming ring.
 */
MATCH void EMI_OnCdReady(u8 status, u8* result) {
    u8*           read_progress;
    CdlLOC*       current_pos;
    s32           callback_ready;
    u32           transfer_size;
    u32           pending;
    u16           state;
    s32           slot;
    u8            next;
    u8*           cursor;
    volatile u32* counter;

    read_progress  = &g_EmiStreamState;
    callback_ready = *read_progress;
    if (callback_ready != 1) {
        return;
    }

    if (CdReady(1, NULL) == callback_ready) {
        current_pos = &D_8018B490;
        CdGetSector(current_pos, 3);
        if (g_EmiSectorCursor != CdPosToInt(current_pos)) {
            goto fail; /* sector position mismatch */
        }
    } else {
        goto fail; /* CD-ready status mismatch */
    }

    state = g_EmiEntryType;
    if ((state == 0) || (state == 4) || (state == 6) || ((u16)(state - 8) < 2) || (state == 10)) {
        ((void (*)(void))g_EmiEntryHandlers[g_EmiEntryType])();
    } else {
        slot = g_EmiRingSlot;
        if ((g_EmiRingStates[slot] & 0x80) == 0) {
        fail:
            g_EmiReadStatus = 1;
            *read_progress  = 0;
            return;
        }

        transfer_size = g_EmiBytesLeft;
        if (transfer_size >= 0x801) {
            pending                                = transfer_size - 0x800;
            g_EmiBytesLeft                         = pending;
            ((u32*)&g_EmiStreamState)[0x21 + slot] = 0x800;
        } else {
            ((u32*)&g_EmiStreamState)[0x21 + slot] = transfer_size;
            g_EmiBytesLeft                         = 0;
        }

        CdGetSector((void*)(g_EmiRingBase + ((u32)g_EmiRingSlot << 11)), 0x200);
        if ((g_EmiStep == 0) && ((g_EmiFirstWord != *(u32*)(((u32)g_EmiRingSlot << 11) + g_EmiRingBase)) ||
                                 (g_EmiPayloadSector != g_EmiSectorCursor))) {
            g_EmiReadStatus  = 1;
            g_EmiStreamState = 0;
            return;
        }

        ((void (*)(void))g_EmiEntryHandlers[g_EmiEntryType])();
        cursor = (u8*)&g_EmiRingSlot;
        (*cursor)++;
        if ((s8)*cursor == 0x18) {
            *cursor = 1;
        }
    }

    if (g_EmiReadStatus == 0) {
        if (g_EmiBytesLeft == 0) {
            next          = g_EmiNextSlot;
            g_EmiNextSlot = next + 1;
            if (EMI_LoaderNextRead(next) == 0) {
                EMI_LoaderEndStream();
            }
        }

        counter = &g_EmiSectorCursor;
        *counter += 1;
    }
}
