#include "area041_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F4118(void) {
    g_Task->pos.x.fixed += g_Task->vx;
    g_PaletteFades[g_Game.current->unk_13D].offset.red += 2;
    g_PaletteFades[g_Game.current->unk_13D].offset.green += 2;
    g_PaletteFades[g_Game.current->unk_13D].offset.blue += 2;
}
#else
INCLUDE_ASM(func_801F4118);
#endif
