#include "engine/slus/slus.h"

/* adds to the character's power and agility by the kind-selected bytes of the 0x18-stride table
 * Weapon.power and .weight, then by the weapon's own bonus to the stat block.
 */
MATCH void Char_ApplyWeapon(Character* character) {
    Character* record;
    Stats*     stats;
    u8         kind;

    record = character;
    kind   = record->equip.weapon;
    Char_AddStat(&record->stats.power, g_Weapons[kind].power);
    Char_AddStat(&record->stats.agility, -g_Weapons[kind].weight);
    stats = &record->stats;
    switch (kind - WEAPON_DEADLY_BLADE) {
        case 0:
            Char_AddPercent(&stats->critical_chance, 8);
            break;
        case WEAPON_SEEKING_SWORD - WEAPON_DEADLY_BLADE:
            Char_AddStat(&stats->defense, 5);
            Char_AddStat(&stats->agility, 5);
            Char_AddStat(&stats->intelligence, 5);
            break;
        case WEAPON_ASHURAS_SWORD - WEAPON_DEADLY_BLADE:
            Char_AddResistance(&stats->resistances[RES_INDEX_DEATH], 3);
            break;
        case WEAPON_MAGICIAN_ROD - WEAPON_DEADLY_BLADE:
            Char_AddStat(&stats->intelligence, 3);
            break;
        case WEAPON_BERYL_ROD - WEAPON_DEADLY_BLADE:
            Char_AddStat(&stats->intelligence, 5);
            break;
        case WEAPON_BLESSED_STAFF - WEAPON_DEADLY_BLADE:
            Char_AddResistance(&stats->resistances[RES_INDEX_DEATH], 1);
            break;
        case WEAPON_OUROBOROS - WEAPON_DEADLY_BLADE:
            Char_AddStat(&stats->intelligence, 0xA);
            Char_AddResistance(&stats->resistances[RES_INDEX_DEATH], 1);
            Char_AddResistance(&stats->resistances[RES_INDEX_STATUS], 1);
            break;
        case WEAPON_GUNGINIR - WEAPON_DEADLY_BLADE:
            Char_AddPercent(&stats->accuracy, 0xA);
            break;
        case WEAPON_THIEVES_KNIFE - WEAPON_DEADLY_BLADE:
            Char_AddPercent(&stats->surprise_chance, 5);
            Char_AddPercent(&stats->critical_chance, 4);
            break;
        case WEAPON_SLICER - WEAPON_DEADLY_BLADE:
            Char_AddPercent(&stats->critical_chance, 8);
            break;
        case WEAPON_LIFESTEALER - WEAPON_DEADLY_BLADE:
            Char_AddResistance(&stats->resistances[RES_INDEX_DEATH], 3);
            break;
        case WEAPON_HOMING_BOMB - WEAPON_DEADLY_BLADE:
            Char_AddPercent(&stats->accuracy, 0x1E);
            break;
    }
}
