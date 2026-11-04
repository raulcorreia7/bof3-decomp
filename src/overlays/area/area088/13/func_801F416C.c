#include "area088_13.h"

MATCH void func_801F416C(void) {
    u8 mode;

    g_SpadWork->unk_2E -= 0x10;
    if ((s16)g_SpadWork->unk_2E < -0x2F) {
        ACTOR_CLEAR_STATE();
    }

    if (D_801454F2 != 2) {
        mode                 = 1;
        g_SpadWork->state_02 = mode;
    }

    Area_DrawHud(0x10, g_SpadWork->unk_2E);
}
