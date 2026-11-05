#include "area198_13.h"

MATCH void func_801F2E04(void) {
    GFX_FreePaletteSlotOwner(g_Task);
    GFX_StartPaletteAnimation((u8*)g_Task, (u8*)D_801F4324);
    g_Task->unk_2A = 1;
    Actor_SelectScript(0);
}
