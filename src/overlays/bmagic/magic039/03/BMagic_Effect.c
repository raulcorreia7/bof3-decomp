#include "magic039_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC94);

#include "overlays/bmagic/Effect_NextStepOnZeroTick.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH s32 func_801EEF3C(void) {
    u16* id;

    id = (u16*)&g_Battle.action_id;
    switch (*id) {
        case 0x27:
        default:
            return 2;
        case 0xA3:
            return 3;
    }
}

/* func_801EEF64 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFA8(void) {
    BMagicEffectFuncs handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->header.step);
    if ((g_Task->header.flags & 1) && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EFAA4();
        func_801F0054();
        PopMatrix();
    }
}

MATCH void func_801EF070(void) {
    PartyMember* src;

    src                 = (PartyMember*)g_BattleEffectBattler;
    g_Task->pos.x.fixed = src->pos.x.fixed;
    g_Task->pos.y.fixed = src->pos.y.fixed;
    g_Task->pos.z       = src->pos.z;
    g_Task->unk_09      = 0;
    g_Task->timer       = 1;
    g_Task->header.step = g_Task->header.step + 1;
}

MATCH void func_801EF0D4(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 2;
    g_Task->unk_09 = timer;
    if ((timer & BYTE_MASK) == 16) {
        g_Task->timer = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF134(void) {
    u8            timer_next;
    PartyMember** selected;

    g_Task->unk_09 += 1;
    timer_next    = g_Task->timer + 2;
    g_Task->timer = timer_next;
    if ((timer_next & BYTE_MASK) == 0x18) {
        selected = &g_Battle.selected_actor;
        GFX_FreePaletteFadeTarget(*selected);
        g_Task->param.unk_0B = GFX_AllocPaletteFade(*selected, 0, 0, 0, 1);
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF1F4);

/* Counts the effect counter up and fades the palette row the effect claimed down to zero, then steps. */
MATCH void func_801EF320(void) {
    g_Task->unk_09 += 1;
    g_PaletteFades[g_Task->param.unk_0B].offset.red -= 2;
    g_PaletteFades[g_Task->param.unk_0B].offset.green -= 2;
    g_PaletteFades[g_Task->param.unk_0B].offset.blue -= 2;
    if (g_PaletteFades[g_Task->param.unk_0B].offset.red == 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF44C(void) {
    u8 timer_next;

    g_Task->unk_09 += 1;
    timer_next    = g_Task->timer - 2;
    g_Task->timer = timer_next;
    if (!(timer_next & BYTE_MASK)) {
        GFX_FreePaletteFadeTarget(g_Battle.selected_actor);
        func_800AF814(g_Battle.target_selector);
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF4E4(void) {
    Magic039Steps handlers;

    handlers = D_801EEC28;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (ACTOR_IN_USE(*g_Task) && g_Task->header.step != 0) {
        Battle_ProjectRange();
        func_801EF758();
    }
}

INCLUDE_ASM(func_801EF584);

MATCH void func_801EF690(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 16;
    g_Task->unk_09 = timer;
    if (timer == 128) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void Effect_CountDownTimer(void) {
    BMagic_CountDownEffectTimer(8);
}

INCLUDE_ASM(func_801EF758);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EFAA4);

INCLUDE_ASM(func_801F0054);
