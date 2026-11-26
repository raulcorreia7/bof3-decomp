#include "engine/game/00/game_00.h"

/* func_801C2BEC */
/* Applies and flashes the floor damage of the damage cell under the party member, unless bit 0x400 of the game flags is set. */
MATCH void Party_FloorDamageUpdate(void) {
    u16               flags;
    FloorDamageColors table;
    u8                index;

    flags = g_Game.flags;

    table = g_PartyFloorDamageColors;
    if (flags & 0x400) {
        index = GAME_NONE;
    } else {
        if (Game_TestMapCells(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, TASK(Actor)->voice_flags.scene_flag, 0x80, 0) & BYTE_MASK) {
            index = PARTY_FLOOR_DAMAGE_HP_LIGHT;
        } else if (Game_TestMapCells(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, TASK(Actor)->voice_flags.scene_flag, 0x81, 0) & BYTE_MASK) {
            index = PARTY_FLOOR_DAMAGE_HP_MEDIUM;
        } else if (Game_TestMapCells(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, TASK(Actor)->voice_flags.scene_flag, 0x82, 0) & BYTE_MASK) {
            index = PARTY_FLOOR_DAMAGE_HP_HEAVY;
        } else if (Game_TestMapCells(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, TASK(Actor)->voice_flags.scene_flag, 0x83, 0) & BYTE_MASK) {
            index = PARTY_FLOOR_DAMAGE_HP_SEVERE;
        } else if (Game_TestMapCells(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, TASK(Actor)->voice_flags.scene_flag, 0x84, 0) & BYTE_MASK) {
            index = PARTY_FLOOR_DAMAGE_POISON;
        } else if (Game_TestMapCells(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, TASK(Actor)->voice_flags.scene_flag, 0x85, 0) & BYTE_MASK) {
            index = PARTY_FLOOR_DAMAGE_CONFUSION;
        } else if (Game_TestMapCells(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, TASK(Actor)->voice_flags.scene_flag, 0x86, 0) & BYTE_MASK) {
            index = PARTY_FLOOR_DAMAGE_AP_LIGHT;
        } else if (Game_TestMapCells(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, TASK(Actor)->voice_flags.scene_flag, 0x87, 0) & BYTE_MASK) {
            index = PARTY_FLOOR_DAMAGE_AP_MEDIUM;
        } else {
            index = (Game_TestMapCells(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, TASK(Actor)->voice_flags.scene_flag, 0x88, 0) & BYTE_MASK) ? PARTY_FLOOR_DAMAGE_AP_HEAVY : GAME_NONE;
        }
    }
    if (index != GAME_NONE) {
        Party_FloorDamageApply(index);
        Party_FlashDamage(table.colors[index]);
    }
}
