#include "battle_15.h"

/* Applies the equipment chosen in the item list: moves the six slots through Item_Remove and Item_Add and rebuilds the stats. */
/* func_8009A744 */
MATCH void Battle_ApplyEquipment(void) {
    u8* slots[6];
    u8* record;
    u8* cell;
    u8  character_index;
    u8  value;
    u32 i;
    u32 slot;
    u32 member_offset;
    u32 party_slot;

    record   = (u8*)&g_Characters[g_CharSlot[g_PartyBattleOrder[g_UIPanelTasks[18].unk_0C]]];
    slots[0] = record + 0xE;
    slots[1] = record + 0xF;
    slots[2] = record + 0x10;
    slots[3] = record + 0x11;
    slots[4] = record + 0x12;
    slots[5] = record + 0x13;
    for (i = 0; (u8)i < 6; i++) {
        slot  = (u8)i;
        value = s_BattleEquipment[slot];
        if (value != 0 && value != *slots[slot]) {
            Item_Remove(D_800B44B0[slot], value, 1, 0);
            Item_Add(D_800B44B0[slot], *slots[slot], 1, 0);
            *slots[slot] = s_BattleEquipment[slot];
        }
    }
    Char_RebuildStats((Character*)record);
    {
        u8* count = &g_BattlePartyCount;

        i = 0;
        if (*count != 0) {
            do {
                party_slot    = (u8)i;
                member_offset = party_slot << 2;
                member_offset += party_slot;
                member_offset <<= 6;
                record                                     = (u8*)g_Game.members[0].chr.name + member_offset;
                character_index                            = g_Game.members[0].chr.name[member_offset + 0xC8];
                cell                                       = (u8*)&g_Characters[character_index];
                ((Character*)record)->equip.weapon         = ((Character*)cell)->equip.weapon;
                ((Character*)record)->equip.shield         = ((Character*)cell)->equip.shield;
                ((Character*)record)->equip.helmet         = ((Character*)cell)->equip.helmet;
                ((Character*)record)->equip.armor          = ((Character*)cell)->equip.armor;
                ((Character*)record)->equip.accessories[0] = ((Character*)cell)->equip.accessories[0];
                ((Character*)record)->equip.accessories[1] = ((Character*)cell)->equip.accessories[1];
                memcpy(record + 0x3C, cell + 0x1C, 0x10);
                memcpy(record + 0x4C, cell + 0x2C, 0x10);
                i++;
            } while ((u8)i < *count);
        }
    }
    Battle_ApplyFormationStats();
    {
        u8* dst_base = D_80145F20;
        u8* src_base = dst_base + 0x20;

        i = 0;
        do {
            member_offset = (u8)i * BATTLE_PARTY_STRIDE;
            if (ACTOR_IN_USE(g_Game.members[(u8)i])) {
                memcpy((u8*)(member_offset + (u32)dst_base), (u8*)(member_offset + (u32)src_base), 0x20);
            }
            i++;
        } while ((u8)i < 3);
    }
    i = 0;
    func_800A4458();
    if (g_BattlePartyCount != 0) {
        do {
            Battle_RescaleStats((u8)i);
            i++;
        } while ((u8)i < g_BattlePartyCount);
    }
}
