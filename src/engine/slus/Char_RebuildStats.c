#include "engine/slus/slus.h"

/* Playable-character attributes copied from base stats at +0x3C to current stats at +0x1C.
 * Char_RebuildStats then applies fatigue and equipment; @source: wiki:data/records. */
typedef struct {
    u8 data[32];
} CharacterAttributes;

/* copies the base block over the live block, refreshes derived
 * state, then retunes per-slot values against the matching table entry.
 */
MATCH void Char_RebuildStats(Character* record) {
    s32 prod;
    s32 quot;
    s32 next;
    u16 cur;
    u8  index;
    u8* entry;

    *(CharacterAttributes*)&record->stats.max_hp = *(CharacterAttributes*)&record->base.max_hp;

    Char_ApplyWeapon((u8*)record);
    Char_ApplyArmor((u8*)record);
    Char_ApplyAccessories((u8*)record);
    Char_ApplyMaster((u8*)record);

    prod                 = record->base.max_hp * record->fatigue;
    quot                 = (prod + 5) / 10;
    next                 = record->stats.max_hp - quot;
    record->stats.max_hp = next;
    cur                  = next;
    if (cur < record->hp) {
        record->hp = cur;
    }

    if (record->inoculations & 0x1) {
        Char_AddResistance(&record->stats.resistances[0], 2);
    }
    if (record->inoculations & 0x2) {
        Char_AddResistance(&record->stats.resistances[1], 2);
    }
    if (record->inoculations & 0x4) {
        Char_AddResistance(&record->stats.resistances[2], 2);
    }
    if (record->inoculations & 0x8) {
        Char_AddResistance(&record->stats.resistances[3], 2);
    }
    if (record->inoculations & 0x10) {
        Char_AddResistance(&record->stats.resistances[4], 2);
    }
    if (record->inoculations & 0x20) {
        Char_AddResistance(&record->stats.resistances[6], 2);
    }
    if (record->inoculations & 0x40) {
        Char_AddResistance(&record->stats.resistances[7], 2);
    }
    if (record->inoculations & 0x80) {
        Char_AddResistance(&record->stats.resistances[8], 2);
    }

    for (index = 0; index < CHARACTER_COUNT; index++) {
        if (record == &g_Characters[index]) {
            entry = D_8014866C + index * 5;
            if (record->stats.surprise_chance != 0) {
                Char_AddPercent(&record->stats.surprise_chance, entry[0]);
            }
            if (record->stats.reprisal_chance != 0) {
                Char_AddPercent(&record->stats.reprisal_chance, entry[1]);
            }
            if (record->stats.critical_chance != 0) {
                Char_AddPercent(&record->stats.critical_chance, entry[2]);
            }
            if (record->stats.evasion != 0) {
                Char_AddPercent(&record->stats.evasion, entry[3]);
            }
            if (record->stats.accuracy != 0) {
                Char_AddPercent(&record->stats.accuracy, entry[4]);
            }
        }
    }
}
