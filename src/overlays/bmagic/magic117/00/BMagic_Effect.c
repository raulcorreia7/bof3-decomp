#include "magic117_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/func_801EEC24.h"

MATCH void func_801EEC90(void) {
    PartyMember** actor;

    actor = &g_Battle.selected_actor;
    GFX_PaletteFreeFadeTarget(*actor);
    BMAGIC_WORK->param.unk_0B = GFX_PaletteAllocFade(*actor, 0, 0, 0, 1);
    BMAGIC_WORK->unk_09       = 0;
    BMAGIC_WORK->timer        = 2;
    BMAGIC_WORK->header.mode += 1;
}

/* Brightens the effect palette. */
/* func_801EED2C */
MATCH void Effect_BrightenPalette(void) {
    /* kept: a helper taking the step shares func_801EF0F8's body but drops retail's 16-byte frame here, 4 bytes
     * short; the channels need ++ and --. */
    g_PaletteFades[BMAGIC_WORK->param.unk_0B].offset.r++;
    g_PaletteFades[BMAGIC_WORK->param.unk_0B].offset.g++;
    g_PaletteFades[BMAGIC_WORK->param.unk_0B].offset.b++;
    if (++BMAGIC_WORK->unk_09 == 0x10) {
        BMAGIC_WORK->header.mode++;
    }
}

MATCH void func_801EEE40(void) {
    g_PaletteFades[BMAGIC_WORK->param.unk_0B].offset.r--;
    g_PaletteFades[BMAGIC_WORK->param.unk_0B].offset.g--;
    g_PaletteFades[BMAGIC_WORK->param.unk_0B].offset.b--;
    if (--BMAGIC_WORK->unk_09 == 0) {
        if (--BMAGIC_WORK->timer != 0) {
            BMAGIC_WORK->header.mode--;
        } else {
            GFX_PaletteFreeFadeTarget(g_Battle.selected_actor);
            Battle_FadePoisonedBattler(g_Battle.target_selector);
            BMAGIC_WORK->header.mode++;
        }
    }
}

#include "shared/Effect_PlayOnce.h"

MATCH void func_801EF000(void) {
    Magic117Steps handlers;

    handlers = D_801EEC14;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);
}

#include "overlays/bmagic/shared/Effect_StartPaletteFade.h"

MATCH void func_801EF0F8(void) {
    g_PaletteFades[BMAGIC_WORK->param.unk_0B].offset.r--;
    g_PaletteFades[BMAGIC_WORK->param.unk_0B].offset.g--;
    g_PaletteFades[BMAGIC_WORK->param.unk_0B].offset.b--;
    if (++BMAGIC_WORK->unk_09 == 0x10) {
        BMAGIC_WORK->header.mode++;
    }
}

MATCH void func_801EF20C(void) {
    g_PaletteFades[BMAGIC_WORK->param.unk_0B].offset.r++;
    g_PaletteFades[BMAGIC_WORK->param.unk_0B].offset.g++;
    g_PaletteFades[BMAGIC_WORK->param.unk_0B].offset.b++;
    if (--BMAGIC_WORK->unk_09 == 0) {
        GFX_PaletteFreeFadeTarget(g_Battle.selected_actor);
        Battle_FadePoisonedBattler(g_Battle.target_selector);
        BMAGIC_WORK->header.mode++;
    }
}

MATCH void Effect_PlayOnce2(void) {
    BATTLE_PLAY_ONCE();
}
