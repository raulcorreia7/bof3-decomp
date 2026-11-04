#include "engine/slus/slus.h"

/* adjusts the record's 16-bit fields at +0x20 and +0x24 by the kind-selected bytes of the 0x18-stride table
 * D_801C90EE/D_801C90EC, then by kind - 0xD nudges the counters in the +0x1C record body.
 */
MATCH void Char_ApplyWeapon(void* character) {
    /* FAKE: record base pinned to s1; the retail allocation keeps kind in s2. */
    MATCH_REG(u8*, record, "s1");
    u8  kind;
    s32 offset;

    record = character;
    kind   = record[0x0E];
    offset = kind * 0x18;
    Char_AddStat((u16*)(record + 0x20), D_801C90EE[offset]);
    Char_AddStat((u16*)(record + 0x24), -D_801C90EC[offset]);
    record += 0x1C;
    switch (kind - WEAPON_DEADLY_BLADE) {
        case 0:
            Char_AddPercent(record + 0x1A, 8);
            break;
        case WEAPON_SEEKING_SWORD - WEAPON_DEADLY_BLADE:
            Char_AddStat((u16*)(record + 6), 5);
            Char_AddStat((u16*)(record + 8), 5);
            Char_AddStat((u16*)(record + 0xA), 5);
            break;
        case WEAPON_ASHURAS_SWORD - WEAPON_DEADLY_BLADE:
            Char_AddResistance(record + 0x17, 3);
            break;
        case WEAPON_MAGICIAN_ROD - WEAPON_DEADLY_BLADE:
            Char_AddStat((u16*)(record + 0xA), 3);
            break;
        case WEAPON_BERYL_ROD - WEAPON_DEADLY_BLADE:
            Char_AddStat((u16*)(record + 0xA), 5);
            break;
        case WEAPON_BLESSED_STAFF - WEAPON_DEADLY_BLADE:
            Char_AddResistance(record + 0x17, 1);
            break;
        case WEAPON_OUROBOROS - WEAPON_DEADLY_BLADE:
            Char_AddStat((u16*)(record + 0xA), 0xA);
            Char_AddResistance(record + 0x17, 1);
            Char_AddResistance(record + 0x16, 1);
            break;
        case WEAPON_GUNGINIR - WEAPON_DEADLY_BLADE:
            Char_AddPercent(record + 0x1C, 0xA);
            break;
        case WEAPON_THIEVES_KNIFE - WEAPON_DEADLY_BLADE:
            Char_AddPercent(record + 0x18, 5);
            Char_AddPercent(record + 0x1A, 4);
            break;
        case WEAPON_SLICER - WEAPON_DEADLY_BLADE:
            Char_AddPercent(record + 0x1A, 8);
            break;
        case WEAPON_LIFESTEALER - WEAPON_DEADLY_BLADE:
            Char_AddResistance(record + 0x17, 3);
            break;
        case WEAPON_HOMING_BOMB - WEAPON_DEADLY_BLADE:
            Char_AddPercent(record + 0x1C, 0x1E);
            break;
    }
}
