#include "game_00.h"

/* K&R call forwards a0 untouched as the mode argument. */

MATCH void func_801C329C(void) {
    s32        index;
    Actor*     work;
    s32        found;
    u8         total;
    u8         id;
    u8         sel;
    ActorSlot* record;
    u16        value30;
    u8         slot;
    u32        scratch[4];
    u32*       scratch_ptr;

    scratch_ptr = scratch;
    found       = 0;
    total       = Party_CountOrder(0);
    if (g_GameRequestFlags & 1) {
        index = 0;
        if ((s16)total > 0) {
            do {
                sel = g_CharSlot[D_80144F5A[index]];
                if (g_SaveData.characters[sel].status & STATUS_POISONED) {
                    found = 1;
                }
                index++;
            } while (index < (s16)total);
        }
    } else {
        if (g_SaveData.characters[g_GameState->slot_13C].status & STATUS_POISONED) {
            found = 1;
        }
    }
    if ((found & BYTE_MASK) != 0) {
        g_GameState->flags_118--;
        found = 0;
        if (g_GameState->flags_118 == 0) {
            g_GameState->flags_118 = 0x0A;
            func_801C308C(1);
            if (g_GameRequestFlags & 1) {
                index = 0;
                if ((s16)total > 0) {
                    do {
                        id  = D_80144F5A[index];
                        sel = g_CharSlot[id];
                        if ((g_SaveData.characters[sel].status & STATUS_POISONED) &&
                            ((Char_LoseHP(1, id) & HALF_MASK) != 0)) {
                            found = 1;
                        }
                        index++;
                    } while (index < (s16)total);
                }
            } else {
                if ((Char_LoseHP(1, g_GameState->slot_index_79) & HALF_MASK) != 0) {
                    found = 1;
                }
            }
        }
        if ((found & BYTE_MASK) != 0) {
            slot = Actor_FindFreeSlot() & BYTE_MASK;
            if (slot != GAME_NONE) {
                g_ActorSlots[slot].header.flags = 1;
                g_ActorSlots[slot].type         = 0x41;
                g_ActorSlots[slot].unk_08       = g_Task->direction_08;
                COORD_INT(g_ActorSlots[slot].x) = g_Task->unk_2E;
                value30                         = g_Task->unk_30;
                g_ActorSlots[slot].unk_27       = 0;
                g_ActorSlots[slot].unk_06       = 1;
                record                          = g_ActorSlots;
                work                            = g_Task;
                COORD_INT(record[slot].y)       = value30;
                g_ActorSlots[slot].link         = work->unk_05;
            }
        }
    }
}
