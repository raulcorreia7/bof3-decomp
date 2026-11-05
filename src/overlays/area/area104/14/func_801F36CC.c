#include "area104_14.h"

MATCH void func_801F36CC(void) {
    g_SpadWork->unk_2E -= 0x10;
    if ((s16)g_SpadWork->unk_2E < -0x2F) {
        g_SpadWork->state_02 = 0;
    }

    if (D_801454F2 != 2) {
        g_SpadWork->state_02 = 1;
    }

    Area_DrawHud(0x10, g_SpadWork->unk_2E);
}
