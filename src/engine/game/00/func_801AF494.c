#include "game_00.h"

MATCH bool func_801AF494(u8 test, u8 character_id, u8 category, u8 item_id) {
    u8 index;

    if (item_id == ITEM_NOTHING) {
        return false;
    }
    switch (test) {
        case 0:
            return true;
        case 1:
            if (category != ITEM_CAT_ITEM) {
                return false;
            }
            index = item_id;
            if ((g_Items[index].flags & 0x1) == 0) {
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
            if (Item_GetFlags(category, item_id) & 0x2) {
                /* record bit 1 set */
                goto ret1;
            }
            return false;
        case 3:
            if ((Item_GetFlags(category, item_id) & 0x8) == 0) {
                /* record bit 3 clear */
                goto ret1;
            }
            return false;
        case 4:
            if (((Item_GetEquipability(category, item_id) & BYTE_MASK) >> character_id) & 0x1) {
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
