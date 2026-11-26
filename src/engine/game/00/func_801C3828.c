#include "game_00.h"

MATCH void func_801C3828(void) {
    if (Char_CountEquipped(g_Game.current->character_index, EQUIP_GROUP_ACCESSORY, 0x16) & BYTE_MASK) {
        Char_HPAdd(1, g_Game.current->chr.character_id);
    }
    if (Char_CountEquipped(g_Game.current->character_index, EQUIP_GROUP_ACCESSORY, 0x17) & BYTE_MASK) {
        Char_HPAdd(1, g_Game.current->chr.character_id);
    }
    if (Char_CountEquipped(g_Game.current->character_index, EQUIP_GROUP_ARMOR, 0x1F) & BYTE_MASK) {
        Char_HPAdd(1, g_Game.current->chr.character_id);
    }
}
