#include "shop_00.h"

MATCH void func_801D472C(void) {
    u8* state;
    u8  count;

    D_801E6110 = 0;
    D_801E60EC = SAVE_WAIT_PROBE;
    MENU_DRAW_HEADER();
    D_801E6080 = 0;
    /* Pointer form: retail keeps one base register across the counter read and
     * the store, which symbol accesses would re-materialize. */
    state      = &D_80148652;
    count      = *state;
    *state     = 0x13;
    D_80148654 = 2;
    D_801E6094 = count + 1;
}
