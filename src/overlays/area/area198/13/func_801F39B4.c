#include "area198_13.h"

MATCH void func_801F39B4(void) {
    GFX_FreePaletteSlotOwner((s32)g_Task);
    GFX_StartPaletteAnimation((u8*)g_Task, D_801F4368);
    g_Task->unk_2A = 1;
    g_Task->flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    Actor_SelectScript(0);
}
