#include "game_00.h"

/* func_801C2E34 */
MATCH void Char_SetCharacterId(u8 index) {
    GameMenuSlots table;
    u8*           entry;
    s32           record_index1;
    s32           record_index2;
    s32           record_index3;
    u8            flags;

    table = D_80195FF8;
    entry = (u8*)table.entries + index * 3;
    Char_LoseHP(entry[0], g_Game.current->chr.character_id);
    Char_SpendAP(entry[1], g_Game.current->chr.character_id);
    if (entry[2] & 0x80) {
        g_Game.current->u.field.flags_118 = 0x0A;
    }
    if (entry[2] & 0x20) {
        g_Game.current->u.field.countdown_119 = 0x28;
    }
    record_index1 = g_GameState->character_index;
    if ((u32)(g_Characters[record_index1].stats.max_hp >> 2) >= g_Characters[record_index1].hp) {
        g_Characters[record_index1].status |= STATUS_LOW_HP;
        g_GameState->chr.status |= STATUS_LOW_HP;
    }
    flags         = entry[2];
    record_index2 = g_GameState->character_index;
    g_Characters[record_index2].status |= flags;
    if ((u8)func_801C38F4(g_GameState->character_index, 3, 8) != 0) {
        record_index3 = g_GameState->character_index;
        g_Characters[record_index3].status &= ~STATUS_CONFUSED;
        g_GameState->u.field.countdown_119 = 0;
    }
}
