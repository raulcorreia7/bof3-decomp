#include "scena02_00.h"
#include "area/map.h"
#include "area/spad.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FB2F8(void) {
}

MATCH void func_801FB300(void) {
    u8* step = &g_SceneState.step_05;

    if (*step == 0) {
        Party_AddZenny(0x32, 0);
        SYS_SetFlag(g_SceneFlags, 0x23);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        Game_ClearScriptActive();
        *step                 = 0;
        g_SceneState.state_04 = 0;
    }
}

INCLUDE_ASM(func_801FB36C);
