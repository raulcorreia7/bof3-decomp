#include "game_00.h"

/* func_801AF494 */
MATCH bool Item_PassesTest(u8 test, u8 character_id, u8 category, u8 item_id) {
    u8 index;

    if (item_id == ITEM_NOTHING) {
        return false;
    }
    switch (test) {
        case ITEM_TEST_ANY:
            return true;
        case ITEM_TEST_TARGET_BOTH:
            if (category != ITEM_CATEGORY_ITEM) {
                return false;
            }
            index = item_id;
            if ((g_Items[index].flags & ITEM_TARGET_BOTH) == 0) {
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
        case ITEM_TEST_SELECTABLE:
            if (Item_GetFlags(category, item_id) & ITEM_TARGET_SELECTABLE) {
                goto ret1;
            }
            return false;
        case ITEM_TEST_SELLABLE:
            if ((Item_GetFlags(category, item_id) & ITEM_UNSELLABLE) == 0) {
                goto ret1;
            }
            return false;
        case ITEM_TEST_EQUIPPABLE:
            if (((Item_GetEquipability(category, item_id) & BYTE_MASK) >> character_id) & 0x1) {
                goto ret1;
            }
            return false;
        default:
            return true;
    }
ret1:
    return true;
}
