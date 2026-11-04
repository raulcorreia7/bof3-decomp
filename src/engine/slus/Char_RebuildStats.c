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
    u8  idx;
    u8* entry;

    *(CharacterAttributes*)&record->max_hp = *(CharacterAttributes*)&record->base_hp;

    Char_ApplyWeapon((u8*)record);
    Char_ApplyArmor((u8*)record);
    Char_ApplyAccessories((u8*)record);
    Char_ApplyMaster((u8*)record);

    prod           = record->base_hp * record->fatigue;
    quot           = (prod + 5) / 10;
    next           = record->max_hp - quot;
    record->max_hp = next;
    cur            = next;
    if (cur < record->current_hp) {
        record->current_hp = cur;
    }

    if (record->inoculations & 1) {
        Char_AddResistance(&record->resistances[0], 2);
    }
    if (record->inoculations & 2) {
        Char_AddResistance(&record->resistances[1], 2);
    }
    if (record->inoculations & 4) {
        Char_AddResistance(&record->resistances[2], 2);
    }
    if (record->inoculations & 8) {
        Char_AddResistance(&record->resistances[3], 2);
    }
    if (record->inoculations & 0x10) {
        Char_AddResistance(&record->resistances[4], 2);
    }
    if (record->inoculations & 0x20) {
        Char_AddResistance(&record->resistances[6], 2);
    }
    if (record->inoculations & 0x40) {
        Char_AddResistance(&record->resistances[7], 2);
    }
    if (record->inoculations & 0x80) {
        Char_AddResistance(&record->resistances[8], 2);
    }

    for (idx = 0; idx < 8; idx++) {
        if (record == &g_Characters[idx]) {
            entry = D_8014866C + idx * 5;
            if (record->surprise_chance != 0) {
                Char_AddPercent(&record->surprise_chance, entry[0]);
            }
            if (record->reprisal_chance != 0) {
                Char_AddPercent(&record->reprisal_chance, entry[1]);
            }
            if (record->critical_chance != 0) {
                Char_AddPercent(&record->critical_chance, entry[2]);
            }
            if (record->evasion != 0) {
                Char_AddPercent(&record->evasion, entry[3]);
            }
            if (record->accuracy != 0) {
                Char_AddPercent(&record->accuracy, entry[4]);
            }
        }
    }
}
