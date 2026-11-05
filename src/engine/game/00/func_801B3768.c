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
    u8     slot_index;
    u32*   spawn_count;

    if (SYS_TestFlag(D_80144FC4, g_Actors[g_GameState->slot_12D].unk_05) != 0) {
        Resource_RequestArea(1);
    } else {
        packed   = g_Actors[g_GameState->slot_12D].unk_18;
        high     = packed >> 8;
        selector = packed;
        low      = selector;
        if (low == GAME_NONE) {
            func_801B5E58((high & BYTE_MASK) * 0x28);
            current_kind = g_Actors[g_GameState->slot_12D].unk_05;
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
            } while ((u32)(index & BYTE_MASK) < 0xCU);
            D_801490E4[0] = 0;
            if (Party_AddItem(selector, high & BYTE_MASK, 1, 0) & BYTE_MASK) {
                kind = g_Actors[g_GameState->slot_12D].unk_05;
                if (kind != GAME_NONE) {
                    SYS_SetFlag(D_80144FC4, kind);
                }
                SND_PlayCue(EMI_CUE_ID(1, 6));
                Resource_RequestArea(GAME_TEXT_SEARCH_FOUND);
                /* Retail increments through a pointer here; a plain `+= 1` merges with the tail above. */
                spawn_count = &D_80145038;
                *spawn_count += 1;
            } else {
                Resource_RequestArea(GAME_TEXT_SEARCH_NO_ROOM);
            }
        }
        slot_index = g_GameState->slot_12D;
        if (!(g_Actors[slot_index].unk_0B & 1)) {
            saved_work = g_SpadWork;
            g_SpadWork = &g_Actors[slot_index];
            Actor_SelectScript(1U);
            g_SpadWork = saved_work;
        }
    }
    work             = g_SpadWork;
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    work->state_02   = (u8)(work->state_02 + 1);
}
