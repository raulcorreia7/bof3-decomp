#include "game_00.h"

MATCH bool func_801AF494(u8 predicate_kind, u8 record_bit, u8 record_kind, u8 record_index) {
    u8 index;

    if (record_index == 0) {
        return false;
    }
    switch (predicate_kind) {
        case 0:
            return true;
        case 1:
            if (record_kind != 0) {
                return false;
            }
            index = record_index;
            if ((g_Items[index].flags & 1) == 0) {
                return false;
            }
            if (index != ITEM_FAERIE_TIARA) {
                return true;
            }
            if ((Area_GetCellCode(D_80145EC6, D_80145ECA) & BYTE_MASK) == 0xAE) {
                /* probe matched: the predicate holds */
                goto ret1;
            }
            return false;
        case 2:
            if (Item_GetFlags(record_kind, record_index) & 2) {
                /* record bit 1 set */
                goto ret1;
            }
            return false;
        case 3:
            if ((Item_GetFlags(record_kind, record_index) & 8) == 0) {
                /* record bit 3 clear */
                goto ret1;
            }
            return false;
        case 4:
            if (((Item_GetEquipability(record_kind, record_index) & BYTE_MASK) >> record_bit) & 1) {
                /* selected record bit set */
                goto ret1;
            }
            return false;
        default:
            return true;
    }
ret1:
    return true;
}
