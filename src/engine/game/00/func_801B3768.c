#include "game_00.h"

/* Spawn counter with no registry row: every branch below that completes a
 * spawn bumps it. */

MATCH void func_801B3768(void) {
    Actor* work;
    Actor* saved_work;
    s32    index;
    s32    low;
    u8     byte_index;
    u32    packed;
    u32    high;
    u8     selector;
    u8*    row;
    u8     kind;
    u8     current_kind;
    u8     actor_slot;
    u32*   spawn_count;

    if (SYS_TestFlag(D_80144FC4, g_Actors[g_Game.current->status.field.slot_12D].unk_05) != 0) {
        Message_Request(1);
    } else {
        packed   = g_Actors[g_Game.current->status.field.slot_12D].unk_18;
        high     = packed >> 8;
        selector = packed;
        low      = selector;
        if (low == GAME_NONE) {
            Game_RewardZenny((high & BYTE_MASK) * 0x28);
            current_kind = g_Actors[g_Game.current->status.field.slot_12D].unk_05;
            if (current_kind != low) {
                SYS_SetFlag(D_80144FC4, current_kind);
            }
            D_80145038 += 1;
        } else {
            row   = Item_GetRecord(low, high & BYTE_MASK);
            index = 0;
            do {
                byte_index                     = index & BYTE_MASK;
                g_TextVariables[0][byte_index] = row[byte_index];
                index += 1;
            } while ((index & BYTE_MASK) < 0xCU);
            D_801490E4[0] = 0;
            if (Item_Add(selector, high & BYTE_MASK, 1, 0) & BYTE_MASK) {
                kind = g_Actors[g_Game.current->status.field.slot_12D].unk_05;
                if (kind != GAME_NONE) {
                    SYS_SetFlag(D_80144FC4, kind);
                }
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
                Message_Request(GAME_TEXT_SEARCH_FOUND);
                /* Retail increments through a pointer here; a plain `+= 1` merges with the tail above. */
                spawn_count = &D_80145038;
                *spawn_count += 1;
            } else {
                Message_Request(GAME_TEXT_SEARCH_NO_ROOM);
            }
        }
        actor_slot = g_Game.current->status.field.slot_12D;
        if (!(g_Actors[actor_slot].param.unk_0B & 0x1)) {
            saved_work = g_Task;
            g_Task     = &g_Actors[actor_slot];
            Actor_SelectScript(1U);
            g_Task = saved_work;
        }
    }
    work              = g_Task;
    g_GameStateIndex  = GAME_REQUEST_MESSAGE;
    work->header.step = (work->header.step + 1);
}
