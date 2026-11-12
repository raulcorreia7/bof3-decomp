#include "magic076_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC28);

INCLUDE_ASM(func_801EED48);

/* func_801EEF5C */
#include "overlays/bmagic/Effect_PreparePalette.h"

#include "overlays/bmagic/Effect_BrightenPalette.h"

/* func_801EF11C */
MATCH void Effect_NextStep(void) {
    BMagic_AdvanceEffectStep(1);
}

MATCH void Effect_DarkenPalette(void) {
    g_PaletteFades[g_Task->timer].offset.red--;
    g_PaletteFades[g_Task->timer].offset.green--;
    g_PaletteFades[g_Task->timer].offset.blue--;
    if (--g_Task->unk_09 == 0) {
        GFX_FreePaletteFadeTarget(g_Battle.selected_actor);
        g_Task->header.mode++;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* Whether the queued action is an ability other than Raise Dead (the spell or the skill). */
MATCH u8 func_801EF2E8(void) {
    if (LOBU(g_Battle.action_type) == BATTLE_ACTION_ABILITY) {
        switch (LOHU(g_Battle.action_id)) {
            case ABILITY_RAISE_DEAD:
            case ABILITY_RAISE_DEAD_SKILL:
                return 0;
            default:
                return 1;
            case ABILITY_RESURRECT:
                return 1;
        }
    }
    return 0;
}

/* func_801EF330 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF374(void) {
    SYS_DISPATCH_BYTE(D_801F048C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
        func_801EF698();
    }
}

MATCH void func_801EF3F4(void) {
    PartyMember* work;
    u8           timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->unk_04    = g_BattleEffectBattler->unk_04;
        work              = g_Task;
        work->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        work->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        work->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + 0x00C00000;
        g_Task->unk_09    = 0;
        g_Task->timer     = 60;
        g_Task->header.step++;
    }
}

MATCH void func_801EF4A8(void) {
    PartyMember* battler;
    u8           tick;
    u8           i;
    u8           slot;

    tick           = g_Task->unk_09 + 1;
    g_Task->unk_09 = tick;
    if (tick == 16) {
        for (i = 0; i < D_801F049C[g_Task->unk_04]; i++) {
            slot = BMagic_AllocEffect();
            if (slot != GAME_NONE) {
                battler                                = g_BattleEffectBattler;
                BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
                BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
                BMAGIC_EFFECT_SLOTS[slot].target.party = battler;
                BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = RANDOM_MASK(0xF) + 16;
                g_BattleEffectBattler->param.unk_0B += 1;
            }
        }
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EF698);

MATCH void func_801EF8A8(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 6), 1, g_Task);
}

INCLUDE_ASM(func_801EF8EC);

INCLUDE_ASM(func_801EFA60);

MATCH void func_801EFC30(void) {
    s32  phase;
    s32  b;
    s16* angle_cell;
    u8   count;

    angle_cell = &D_1F800004;
    phase      = g_Task->param.unk_0B & 0xF;
    g_Task->unk_0C += 2;
    *angle_cell         = phase << 8;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(*angle_cell) * g_Task->unk_0C;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * g_Task->unk_0C;
    if (g_Task->unk_20 < g_Task->unk_14) {
        b              = g_Task->unk_14 - g_Task->unk_20;
        g_Task->unk_14 = b;
        g_Task->pos.z.fixed += b;
    }
    count          = g_Task->unk_09 + 2;
    g_Task->unk_09 = count;
    if (count == 0x10) {
        g_Task->header.step++;
    }
}

MATCH void func_801EFD60(void) {
    s32  phase;
    s32  b;
    s16* angle_cell;
    u8   count;

    angle_cell = &D_1F800004;
    phase      = g_Task->param.unk_0B & 0xF;
    g_Task->unk_0C += 1;
    *angle_cell         = phase << 8;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(*angle_cell) * g_Task->unk_0C;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * g_Task->unk_0C;
    if (g_Task->unk_20 < g_Task->unk_14) {
        b              = g_Task->unk_14 - g_Task->unk_20;
        g_Task->unk_14 = b;
        g_Task->pos.z.fixed += b;
    }
    if (g_FrameCount & 1) {
        count          = g_Task->unk_09 - 1;
        g_Task->unk_09 = count;
        if (count == 0) {
            g_BattleEffectBattler->param.unk_0B -= 1;
            Actor_Clear();
        }
    }
}

INCLUDE_ASM(func_801EFEA8);

INCLUDE_ASM(func_801F00FC);

/* func_801F03D4 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0438 */
#include "overlays/bmagic/Actor_Clear.h"
