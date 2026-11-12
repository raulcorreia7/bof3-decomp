#include "magic117_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC24.h"

INCLUDE_ASM(func_801EEC90);

MATCH void func_801EED2C(void) {
    /* kept: a helper taking the step shares func_801EF0F8's body but drops retail's 16-byte frame here, 4 bytes
     * short; the channels need ++ and --. */
    g_PaletteFades[g_Task->param.unk_0B].offset.red++;
    g_PaletteFades[g_Task->param.unk_0B].offset.green++;
    g_PaletteFades[g_Task->param.unk_0B].offset.blue++;
    if (++g_Task->unk_09 == 0x10) {
        g_Task->header.mode++;
    }
}

INCLUDE_ASM(func_801EEE40);

#include "shared/Effect_PlayOnce.h"

MATCH void func_801EF000(void) {
    Magic117Steps handlers;

    handlers = D_801EEC14;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);
}

#include "overlays/bmagic/Effect_StartPaletteFade.h"

MATCH void func_801EF0F8(void) {
    g_PaletteFades[g_Task->param.unk_0B].offset.red--;
    g_PaletteFades[g_Task->param.unk_0B].offset.green--;
    g_PaletteFades[g_Task->param.unk_0B].offset.blue--;
    if (++g_Task->unk_09 == 0x10) {
        g_Task->header.mode++;
    }
}

MATCH void func_801EF20C(void) {
    g_PaletteFades[g_Task->param.unk_0B].offset.red++;
    g_PaletteFades[g_Task->param.unk_0B].offset.green++;
    g_PaletteFades[g_Task->param.unk_0B].offset.blue++;
    if (--g_Task->unk_09 == 0) {
        GFX_FreePaletteFadeTarget(g_Battle.selected_actor);
        func_800AF814(g_Battle.target_selector);
        g_Task->header.mode++;
    }
}

MATCH void Effect_PlayOnce2(void) {
    BATTLE_PLAY_ONCE();
}
