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
    u8*    item;
    u8     type;
    u8     current_type;
    u8     actor_slot;
    u32*   spawn_count;

    if (SYS_TestFlag(D_80144FC4, g_Actors[g_Game.current->status.field.slot].unk_05) != 0) {
        UI_MessageRequest(MSG_SYSTEM_NOTHING_FOUND);
    } else {
        packed   = g_Actors[g_Game.current->status.field.slot].unk_18;
        high     = packed >> 8;
        selector = packed;
        low      = selector;
        if (low == GAME_NONE) {
            Game_RewardZenny((high & BYTE_MASK) * 0x28);
            current_type = g_Actors[g_Game.current->status.field.slot].unk_05;
            if (current_type != low) {
                SYS_SetFlag(D_80144FC4, current_type);
            }
            D_80145038 += 1;
        } else {
            item  = Item_GetRecord(low, high & BYTE_MASK);
            index = 0;
            do {
                byte_index                     = index & BYTE_MASK;
                g_TextVariables[0][byte_index] = item[byte_index];
                index += 1;
            } while ((index & BYTE_MASK) < 0xCU);
            D_801490E4[0] = 0;
            if (Item_Add(selector, high & BYTE_MASK, 1, 0) & BYTE_MASK) {
                type = g_Actors[g_Game.current->status.field.slot].unk_05;
                if (type != GAME_NONE) {
                    SYS_SetFlag(D_80144FC4, type);
                }
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
                UI_MessageRequest(GAME_TEXT_SEARCH_FOUND);
                /* Retail increments through a pointer here; a plain `+= 1` merges with the tail above. */
                spawn_count = &D_80145038;
                *spawn_count += 1;
            } else {
                UI_MessageRequest(GAME_TEXT_SEARCH_NO_ROOM);
            }
        }
        actor_slot = g_Game.current->status.field.slot;
        if (!(g_Actors[actor_slot].param.unk_0B & 0x1)) {
            saved_work = SELF(Actor);
            SELF_SET(&g_Actors[actor_slot]);
            Script_Select(1U);
            SELF_SET(saved_work);
        }
    }
    work              = SELF(Actor);
    g_GameStateIndex  = GAME_REQUEST_MESSAGE;
    work->header.step = (work->header.step + 1);
}
