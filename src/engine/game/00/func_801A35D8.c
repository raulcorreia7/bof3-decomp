#include "game_00.h"

MATCH void func_801A35D8(void) {
    g_CurrentActor->unk_93 = (s8)GFX_AllocPaletteFade((u8*)g_Task, 0x1F, 0x1F, 0x1F, 1);
    g_Task->flags &= ~ACTOR_FLAG_HIDDEN;
    g_Task->unk_04 = 1;
}
