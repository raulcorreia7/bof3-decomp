#include "battle_15.h"

MATCH void func_800AC870(s32 entry_id, PartyMember* source_record, s32 mode) {
    PartyMember* dst;

    dst = (PartyMember*)Battle_FindActorEntry(entry_id & BYTE_MASK);
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
            WorldPos_Copy(&dst->pos, &source_record->pos);
            break;
    }
}
