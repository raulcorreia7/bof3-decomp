#include "shop_00.h"

/* Stock list (stride 0x140 per entry) and item-name table (stride 0xA4). */

MATCH void func_801D3560(u16* result_code) {
    u8         i;
    u8         item;
    Character* entry;

    *result_code = 100;
    for (i = 0; i < Party_CountOrder(PARTY_ORDER_FIELD); i++) {
        /* Shift form: it keeps the table symbol in the load's immediate field,
         * which `i * 0x140` does not. */
        item  = g_BattlePartyBattlers[i].character_index;
        entry = &g_Characters[item];
        if (entry->equip.accessories[0] == ACCESSORY_COUPONS) {
            *result_code = 0x50;
            break;
        }
        if (entry->equip.accessories[1] == ACCESSORY_COUPONS) {
            *result_code = 0x50;
            break;
        }
    }
    /* FAKE: retail reads Item_VitalHas as u8(s32). */
    if (((u8 (*)(s32))Item_VitalHas)(VITAL_ITEM_FLIER) != 0) {
        /* Unsigned compare matches retail's range test on the narrowed byte. */
        if ((u32)(D_80148699 - 6) < 2) {
            *result_code = 0x46;
        }
    }
}
