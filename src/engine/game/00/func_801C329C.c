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
    total       = Party_CountOrder(PARTY_ORDER_FIELD);
    if (g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP) {
        index = 0;
        if ((s16)total > 0) {
            do {
                sel = g_CharSlot[g_PartyFieldOrder[index]];
                if (g_Characters[sel].status & STATUS_POISONED) {
                    found = 1;
                }
                index++;
            } while (index < (s16)total);
        }
    } else {
        if (g_Characters[g_Game.current->character_index].status & STATUS_POISONED) {
            found = 1;
        }
    }
    if ((found & BYTE_MASK) != 0) {
        g_Game.current->u.field.flags_118--;
        found = 0;
        if (g_Game.current->u.field.flags_118 == 0) {
            g_Game.current->u.field.flags_118 = 0x0A;
            func_801C308C(1);
            if (g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP) {
                index = 0;
                if ((s16)total > 0) {
                    do {
                        id  = g_PartyFieldOrder[index];
                        sel = g_CharSlot[id];
                        if ((g_Characters[sel].status & STATUS_POISONED) && ((Char_LoseHP(1, id) & HALF_MASK) != 0)) {
                            found = 1;
                        }
                        index++;
                    } while (index < (s16)total);
                }
            } else {
                if ((Char_LoseHP(1, g_Game.current->chr.character_id) & HALF_MASK) != 0) {
                    found = 1;
                }
            }
        }
        if ((found & BYTE_MASK) != 0) {
            slot = Actor_FindFreeSlot() & BYTE_MASK;
            if (slot != GAME_NONE) {
                g_ActorSlots[slot].header.flags     = 1;
                g_ActorSlots[slot].type             = 0x41;
                g_ActorSlots[slot].unk_08           = g_Task->direction_08;
                COORD_INT(g_ActorSlots[slot].pos.x) = g_Task->screen_x;
                value30                             = g_Task->screen_y;
                g_ActorSlots[slot].unk_27           = 0;
                g_ActorSlots[slot].unk_06           = 1;
                record                              = g_ActorSlots;
                work                                = g_Task;
                COORD_INT(record[slot].pos.y)       = value30;
                g_ActorSlots[slot].link             = work->unk_05;
            }
        }
    }
}
