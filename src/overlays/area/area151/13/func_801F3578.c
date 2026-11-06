#include "area151_13.h"

MATCH void func_801F3578(void) {
    Actor* scratch;
    u8     mode;

    scratch = (Actor*)g_Task;
    scratch->unk_2E -= 0x10;
    if ((s16)scratch->unk_2E < -0x2F) {
        scratch->header.step = 0;
    }

    if (D_801454F2 != 2) {
        mode                 = 1;
        scratch              = (Actor*)g_Task;
        scratch->header.step = mode;
    }

    Area_DrawHud(0x10, ((Actor*)g_Task)->unk_2E);
}
