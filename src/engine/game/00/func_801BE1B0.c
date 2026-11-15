#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING s32 func_801BE1B0(u32 index) {
    Actor* row;
    u8**   lists;
    u8*    ids;
    u8*    cursor;
    u8*    values;
    u8*    slots;
    u8*    taken;
    u32    command;
    u32    kind;
    u32    count;
    u32    flags;
    u32    slot;
    s32    i;
    s32    j;
    /* FAKE: unused frame, 16 bytes. */
    FAKE_STACK_PADS(u8, 16);

    lists   = FIELD_PTR(u8*, GAME_TILE_RUN(g_GameAreaId), 0x14);
    ids     = lists[index & BYTE_MASK];
    command = *ids++;
    kind    = command & 0xC0;
    count   = command & 0xF;
    if (kind == 0) {
        if (g_Game.party_size != count)
            return 1;
        values = SP_PTR(u8, 0x00);
        slots  = SP_PTR(u8, 0x04);
        taken  = SP_PTR(u8, 0x08);
        for (i = 0; i < g_Game.party_size; i++)
            taken[i] = g_PartyFieldOrder[i];
        for (i = 0; i < count; i++) {
            if (ids[i] == 0x80) {
                for (j = 0; j < g_Game.party_size && taken[j] == GAME_NONE; j++) {
                }
                if (j == g_Game.party_size)
                    continue;
            } else {
                for (j = 0; j < g_Game.party_size; j++) {
                    row = (Actor*)((u8*)g_Game.members + j * BATTLE_PARTY_STRIDE);
                    if (row->unk_79 == ids[i])
                        break;
                }
                if (j == g_Game.party_size)
                    return 1;
            }
            row       = (Actor*)((u8*)g_Game.members + j * BATTLE_PARTY_STRIDE);
            values[i] = (u8)row->unk_2C;
            slots[i]  = (u8)j;
            taken[j]  = 0xFF;
        }
        for (i = 0; i < count; i++) {
            row                  = (Actor*)((u8*)g_Game.members + slots[i] * BATTLE_PARTY_STRIDE);
            g_PartyFieldOrder[i] = row->unk_79;
        }
        for (i = 0; i + 1 < count; i++) {
            slot = slots[i];
            if (i != slot) {
                Party_SwapMembers(i, slot, 0);
                for (j = i; j < count; j++) {
                    if (slots[j] == i) {
                        slots[j] = (u8)slot;
                        break;
                    }
                }
            }
        }
        ids += count;
    } else if (kind == 0x80) {
        if (g_Game.party_size < count)
            return 1;
    }
    cursor = ids;
    ids += count;
    func_801BE574(g_Game.party_size, cursor);
    flags = command & 0x30;
    if (flags & 0x20)
        g_Game.flags |= GAME_FLAG_SCROLL_LOCK;
    if (flags == 0x30)
        Area_StartScrollRoute(*ids);
    g_Game.flags |= GAME_FLAG_SCRIPT_ACTIVE;
    g_Game.walk_flags |= AREA_WALK_MAP_LOADING;
    return 0;
}
#else
INCLUDE_ASM(func_801BE1B0);
#endif
