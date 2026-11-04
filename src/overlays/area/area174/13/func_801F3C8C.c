#include "area174_13.h"

MATCH void func_801F3C8C(void) {
    GFX_FreePaletteSlotOwner((s32)g_SpadWork);
    GFX_StartPaletteAnimation((u8*)g_SpadWork, (u8*)D_801F66D4);
    g_SpadWork->unk_2A = 1;
    Actor_SelectScript(9);
}
