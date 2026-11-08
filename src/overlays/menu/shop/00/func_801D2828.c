#include "shop_00.h"

/* File-local declarations: shop panel configuration bytes and halfwords. */

MATCH void func_801D2828(void) {
    u8* state;

    D_80148430 = BATTLE_PARTY_STRIDE;
    D_80148432 = 0x3E;
    D_8014842C = 1;
    D_8014842D = 7;
    D_8014842E = 9;
    D_8014842F = 2;
    /* Pointer form: retail keeps one base register across the counter load and
     * the store, which a symbol access would re-materialize. */
    state      = &g_MenuStep.state;
    D_80148436 = 0;
    D_80148437 = 0;
    D_80148438 = 0;
    D_80148439 = 0xFF;
    D_80148434 = 3;
    D_80148435 = 0;
    D_8014843C = 0;
    D_8014843E = 0;
    *state += 1;
}
