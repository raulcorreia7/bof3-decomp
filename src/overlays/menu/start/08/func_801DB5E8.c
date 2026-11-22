#include "start_08.h"

MATCH void func_801DB5E8(void) {
    u8 state;
    u8 pending;

    Menu_DrawClutStrip(g_WindowClut);
    state      = D_80148651;
    pending    = D_80148655;
    D_80148654 = 5;
    D_80148652 = 0;
    D_80148653 = 2;
    D_80148655 = 0;
    D_80148651 = state + 1;
    D_801ED6A0 = pending;
}
