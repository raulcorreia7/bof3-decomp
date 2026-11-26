#include "engine/game/00/game_00.h"

/* func_801C2E34 */
MATCH void Char_SetCharacterId(u8 index) {
    CellEffects table;
    u8*         entry;
    s32         record_index1;
    s32         record_index2;
    s32         record_index3;
    u8          flags;

    table = D_80195FF8;
    entry = (u8*)table.entries + index * 3;
    Char_HPLose(entry[0], g_Game.current->chr.character_id);
    Char_APSpend(entry[1], g_Game.current->chr.character_id);
    if (entry[2] & 0x80) {
        g_Game.current->u.field.flags = 0x0A;
    }
    if (entry[2] & 0x20) {
        g_Game.current->u.field.countdown = 0x28;
    }
    record_index1 = g_GameState->character_index;
    if ((u32)(g_Characters[record_index1].stats.max_hp >> 2) >= g_Characters[record_index1].hp) {
        g_Characters[record_index1].status |= STATUS_LOW_HP;
        g_GameState->chr.status |= STATUS_LOW_HP;
    }
    flags         = entry[2];
    record_index2 = g_GameState->character_index;
    g_Characters[record_index2].status |= flags;
    if ((u8)Char_CountEquipped(g_GameState->character_index, EQUIP_GROUP_ACCESSORY, 8) != 0) {
        record_index3 = g_GameState->character_index;
        g_Characters[record_index3].status &= ~STATUS_CONFUSED;
        g_GameState->u.field.countdown = 0;
    }
}
