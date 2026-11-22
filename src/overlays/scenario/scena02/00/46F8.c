#include "scena02_00.h"
#include "area/map.h"
#include "area/spad.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FB2F8(void) {
}

MATCH void func_801FB300(void) {
    u8* step = &g_ScenarioState.step_05;

    if (*step == 0) {
        Party_AddZenny(0x32, 0);
        SYS_SetFlag(g_SceneFlags, 0x23);
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        Game_ClearScriptActive();
        *step                    = 0;
        g_ScenarioState.state_04 = 0;
    }
}
