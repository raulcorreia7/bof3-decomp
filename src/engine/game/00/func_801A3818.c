#include "game_00.h"

MATCH void func_801A3818(void) {
    g_CurrentActor->unk_93 = (s8)GFX_AllocPaletteFade((u8*)g_Task, 0, 0, 0, 1);
    g_Task->unk_04         = 1;
}
