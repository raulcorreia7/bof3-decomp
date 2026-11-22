#include "area008_13.h"

MATCH void func_801F45E4(void) {
    s32* counter;

    counter = &g_Actors[6].pos.x.fixed;
    *counter += 0x800;
}
