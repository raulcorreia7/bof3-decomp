#include "area033_13.h"

MATCH void func_801F353C(void) {
    Actor* scratch;
    u8     mode;

    scratch = g_SpadWork;
    scratch->unk_2E -= 0x10;
    if ((s16)scratch->unk_2E < -0x2F) {
        scratch->state_02 = 0;
    }

    if (D_801454F2 != 2) {
        mode              = 1;
        scratch           = g_SpadWork;
        scratch->state_02 = mode;
    }

    Area_DrawHud(0x10, g_SpadWork->unk_2E);
}
