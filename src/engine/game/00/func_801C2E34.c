#include "game_00.h"

MATCH void func_801C2E34(u8 index) {
    GameMenuSlots table;
    u8*           entry;
    s32           record_index1;
    s32           record_index2;
    s32           record_index3;
    u8            flags;

    table = D_80195FF8;
    entry = (u8*)table.entries + index * 3;
    Char_LoseHp(entry[0], g_GameState->slot_index_79);
    Char_SpendAp(entry[1], g_GameState->slot_index_79);
    if (entry[2] & 0x80) {
        g_GameState->flags_118 = 0x0A;
    }
    if (entry[2] & 0x20) {
        g_GameState->countdown_119 = 0x28;
    }
    record_index1 = g_GameState->slot_13C;
    if ((u32)(g_Characters[record_index1].stats.max_hp >> 2) >= g_Characters[record_index1].current_hp) {
        g_Characters[record_index1].status |= STATUS_LOW_HP;
        ((PartyBattler*)g_GameState)->stats.status |= STATUS_LOW_HP;
    }
    flags         = entry[2];
    record_index2 = g_GameState->slot_13C;
    g_Characters[record_index2].status |= flags;
    if ((u8)func_801C38F4(g_GameState->slot_13C, 3, 8) != 0) {
        record_index3 = g_GameState->slot_13C;
        g_Characters[record_index3].status &= ~STATUS_CONFUSED;
        g_GameState->countdown_119 = 0;
    }
}
