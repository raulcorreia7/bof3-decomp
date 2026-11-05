#include "battle_15.h"

MATCH void func_800AC870(s32 entry_id, PartyBattler* source_record, s32 mode) {
    PartyBattler* dst;

    dst = (PartyBattler*)func_800AC754(entry_id & BYTE_MASK);
    switch (mode & BYTE_MASK) {
        case 0:
            dst->unk_4B = source_record->unk_4B;
            dst->unk_50 = source_record->unk_50;
            dst->unk_54 = source_record->unk_54;
            dst->unk_58 = source_record->unk_58;
            dst->unk_5A = source_record->unk_5A;
            dst->unk_07 |= 0x20;
            break;
        case 1:
            dst->x.raw = source_record->x.raw;
            dst->y.raw = source_record->y.raw;
            dst->z.raw = source_record->z.raw;
            break;
    }
}
