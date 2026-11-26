#include "engine/game/00/game_00.h"

/* func_801C2E34 */
/* Takes the HP and AP of a floor damage from the active party member and starts its poison or confusion. */
MATCH void Party_FloorDamageApply(u8 damage_index) {
    FloorDamages table;
    FloorDamage* damage;
    s32          record_index1;
    s32          record_index2;
    s32          record_index3;
    u8           status;

    table  = g_PartyFloorDamages;
    damage = &table.damages[damage_index];
    Char_HPLose(damage->hp_loss, g_Game.current->chr.character_id);
    Char_APSpend(damage->ap_loss, g_Game.current->chr.character_id);
    if (damage->status & STATUS_POISONED) {
        g_Game.current->u.field.flags = 0x0A;
    }
    if (damage->status & STATUS_CONFUSED) {
        g_Game.current->u.field.countdown = 0x28;
    }
    record_index1 = g_GameState->character_index;
    if ((u32)(g_Characters[record_index1].stats.max_hp >> 2) >= g_Characters[record_index1].hp) {
        g_Characters[record_index1].status |= STATUS_LOW_HP;
        g_GameState->chr.status |= STATUS_LOW_HP;
    }
    status        = damage->status;
    record_index2 = g_GameState->character_index;
    g_Characters[record_index2].status |= status;
    if ((u8)Char_CountEquipped(g_GameState->character_index, EQUIP_GROUP_ACCESSORY, 8) != 0) {
        record_index3 = g_GameState->character_index;
        g_Characters[record_index3].status &= ~STATUS_CONFUSED;
        g_GameState->u.field.countdown = 0;
    }
}
