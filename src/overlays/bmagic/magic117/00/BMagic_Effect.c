#include "magic117_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/func_801EEC24.h"

MATCH void func_801EEC90(void) {
    PartyMember** actor;

    actor = &g_Battle.selected_actor;
    GFX_PaletteFreeFadeTarget(*actor);
    SELF(PartyMember)->param.unk_0B = GFX_PaletteAllocFade(*actor, 0, 0, 0, 1);
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->timer        = 2;
    SELF(PartyMember)->header.mode += 1;
}

/* Brightens the effect palette. */
/* func_801EED2C */
MATCH void Effect_BrightenPalette(void) {
    /* kept: a helper taking the step shares func_801EF0F8's body but drops retail's 16-byte frame here, 4 bytes
     * short; the channels need ++ and --. */
    g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.r++;
    g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.g++;
    g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.b++;
    if (++SELF(PartyMember)->unk_09 == 0x10) {
        SELF(PartyMember)->header.mode++;
    }
}

MATCH void func_801EEE40(void) {
    g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.r--;
    g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.g--;
    g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.b--;
    if (--SELF(PartyMember)->unk_09 == 0) {
        if (--SELF(PartyMember)->timer != 0) {
            SELF(PartyMember)->header.mode--;
        } else {
            GFX_PaletteFreeFadeTarget(g_Battle.selected_actor);
            Battle_FadePoisonedBattler(g_Battle.target_selector);
            SELF(PartyMember)->header.mode++;
        }
    }
}

#include "shared/Effect_PlayOnce.h"

MATCH void func_801EF000(void) {
    Magic117Steps handlers;

    handlers = D_801EEC14;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Self);
}

#include "overlays/bmagic/shared/Effect_StartPaletteFade.h"

MATCH void func_801EF0F8(void) {
    g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.r--;
    g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.g--;
    g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.b--;
    if (++SELF(PartyMember)->unk_09 == 0x10) {
        SELF(PartyMember)->header.mode++;
    }
}

MATCH void func_801EF20C(void) {
    g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.r++;
    g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.g++;
    g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.b++;
    if (--SELF(PartyMember)->unk_09 == 0) {
        GFX_PaletteFreeFadeTarget(g_Battle.selected_actor);
        Battle_FadePoisonedBattler(g_Battle.target_selector);
        SELF(PartyMember)->header.mode++;
    }
}

MATCH void Effect_PlayOnce2(void) {
    BATTLE_PLAY_ONCE();
}
