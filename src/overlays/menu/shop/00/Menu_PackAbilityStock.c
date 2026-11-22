#include "shop_00.h"

/* func_801E1BCC */
MATCH void Menu_PackAbilityStock(void) {
    u8* abilities;
    u8  i;
    u8  j;

    for (i = 0; i < ABILITY_STOCK_SLOT_COUNT - 1; i++) {
        abilities = D_8014546C;
        for (j = 0; j < ABILITY_STOCK_SLOT_COUNT - 1 - i; j++) {
            if (*abilities == 0 && *(abilities + 1) != 0) {
                Menu_SwapBytes6(abilities, abilities + 1);
            }
            abilities++;
        }
    }
}
