#ifndef MENU_ITEM_H
#define MENU_ITEM_H

/* One row of the item table the shop and start-menu sort routines read.
 * `unk_00` is the byte they compare; its role is unverified. */

#include "types.h"

typedef struct AbilityCost {
    u8 unk_00; /* 0x00; value used by the item-sort routines */
    u8 pad_01[0x13];
} AbilityCost;

ASSERT_OFFSET(AbilityCost, unk_00, 0x00);
ASSERT_SIZE(AbilityCost, 0x14);

#endif
