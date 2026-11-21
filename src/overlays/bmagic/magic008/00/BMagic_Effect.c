#include "magic008_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EECF0(void) {
    Magic008FirstSteps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);
}

MATCH void func_801EED5C(void) {
    BattleEffect* slot;
    PartyMember*  work;
    u32           index;
    u8            active;

    g_Task->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&g_Task->pos, &g_BattleEffectBattler->pos);
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->header.mode += 1;
    Battle_SelectActiveBattlerScript(0xC, 2);
    BMAGIC_ALLOC_BATTLER_EFFECT();
    work                                            = g_Task;
    g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
    g_BattleEffects[index & BYTE_MASK].header.mode  = 0;
    g_BattleEffects[index & BYTE_MASK].header.step  = 0;
    g_BattleEffects[index & BYTE_MASK].step_index   = 31;
    g_BattleEffects[index & BYTE_MASK].target.party = work;
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
    SND_QueueSelectionSE(0x100);
}

MATCH void func_801EEF6C(void) {
    if (g_Task->param.unk_0B == 0xFF) {
        Battle_SelectActiveBattlerScript(4, 0);
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        g_Task->header.mode += 1;
    }
}

#include "shared/Effect_StartPlaying.h"

#include "shared/Effect_PlayOnce.h"

MATCH void func_801EF058(void) {
    Magic008SecondSteps handlers;

    handlers = D_801EEC14;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);
}

MATCH void func_801EF0B8(void) {
    BattleEffect* slot;
    PartyMember*  work;
    u32           index;
    u8            active;

    g_Task->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&g_Task->pos, &g_BattleEffectBattler->pos);
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->header.mode += 1;
    Battle_SelectActiveBattlerScript(0xC, 2);
    BMAGIC_ALLOC_BATTLER_EFFECT();
    work                                            = g_Task;
    g_BattleEffects[index & BYTE_MASK].header.mode  = 1;
    g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
    g_BattleEffects[index & BYTE_MASK].header.step  = 0;
    g_BattleEffects[index & BYTE_MASK].step_index   = 31;
    g_BattleEffects[index & BYTE_MASK].target.party = work;
    g_Task->unk_27                                  = Battle_CopyCellPalette(g_BattleEffectBattler);
    g_Task->unk_28                                  = g_BattleEffectBattler->unk_28;
    g_Task->unk_24                                  = g_BattleEffectBattler->unk_24;
    Battle_SetCellPaletteStp(g_Task);
    Battle_ClearCellPaletteEntry(g_Task);
}

MATCH void func_801EF324(void) {
    u16* battle_flags;

    if (g_Task->param.unk_0B == 0xFF) {
        func_800AFC54();
        Battle_SelectActiveBattlerScript(4, 0);
        battle_flags = &g_Battle.flags;
        *battle_flags |= 4;
        Effect_Reset();
    }
}

MATCH void func_801EF384(void) {
    Magic008FirstSteps handlers;

    handlers = D_801EEC20;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);
}

MATCH void func_801EF3F0(void) {
    BattleEffect* slot;
    PartyMember*  work;
    u32           index;
    u8            active;
    u8            i;

    g_Task->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&g_Task->pos, &g_BattleEffectBattler->pos);
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->header.mode += 1;
    Battle_SelectActiveBattlerScript(0xC, 2);
    for (i = 0; i < 3; i++) {
        BMAGIC_ALLOC_BATTLER_EFFECT();
        work                                            = g_Task;
        g_BattleEffects[index & BYTE_MASK].header.mode  = 3;
        g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
        g_BattleEffects[index & BYTE_MASK].header.step  = 0;
        g_BattleEffects[index & BYTE_MASK].step_index   = 31;
        g_BattleEffects[index & BYTE_MASK].unk_0B       = i;
        g_BattleEffects[index & BYTE_MASK].target.party = work;
        g_Task->param.unk_0B++;
    }
    g_Task->unk_27 = Battle_CopyCellPalette(g_BattleEffectBattler);
    g_Task->unk_28 = g_BattleEffectBattler->unk_28;
    g_Task->unk_24 = g_BattleEffectBattler->unk_24;
    Battle_SetCellPaletteStp(g_Task);
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
}

#include "overlays/bmagic/shared/Effect_RestorePaletteAndReleaseActive.h"

MATCH void func_801EF6AC(void) {
    EFFECT_RESTORE_PALETTE_AND_RELEASE_ACTIVE();
}

MATCH void Effect_StartPlaying3(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}

MATCH void func_801EF75C(void) {
    Magic008FirstSteps handlers;

    handlers = D_801EEC30;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);
}

MATCH void func_801EF7C8(void) {
    BattleEffect* slot;
    PartyMember*  work;
    u32           index;
    u8            active;

    g_Task->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&g_Task->pos, &g_BattleEffectBattler->pos);
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->header.mode += 1;
    Battle_SelectActiveBattlerScript(0xC, 2);
    BMAGIC_ALLOC_BATTLER_EFFECT();
    work                                            = g_Task;
    g_BattleEffects[index & BYTE_MASK].header.mode  = 4;
    g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
    g_BattleEffects[index & BYTE_MASK].header.step  = 0;
    g_BattleEffects[index & BYTE_MASK].step_index   = 31;
    g_BattleEffects[index & BYTE_MASK].target.party = work;
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
}

MATCH void func_801EF9D4(void) {
    if (g_Task->param.unk_0B == 0xFF) {
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        Battle_SelectActiveBattlerScript(4, 0);
        g_Task->header.mode += 1;
    }
}

MATCH void Effect_StartPlaying5(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}

MATCH void func_801EFA74(void) {
    Magic008SecondSteps handlers;

    handlers = D_801EEC40;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);
}

#include "overlays/bmagic/shared/Effect_CopyActiveBattlerToSlot.h"

MATCH void func_801EFAD4(void) {
    BattleEffect* slot;
    PartyMember*  work;
    u32           index;
    u8            active;

    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    Battle_SelectActiveBattlerScript(0xC, 2);
    BMAGIC_ALLOC_BATTLER_EFFECT();
    work                                            = g_Task;
    g_BattleEffects[index & BYTE_MASK].header.mode  = 5;
    g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
    g_BattleEffects[index & BYTE_MASK].header.step  = 0;
    g_BattleEffects[index & BYTE_MASK].step_index   = 31;
    g_BattleEffects[index & BYTE_MASK].target.party = work;
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
}

MATCH void func_801EFC90(void) {
    if (g_Task->param.unk_0B == 0xFF) {
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        Battle_SelectActiveBattlerScript(4, 0);
        g_Task->header.mode += 1;
    }
}

MATCH void Effect_StartPlaying7(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}

MATCH void func_801EFD30(void) {
    Magic008SecondSteps handlers;

    handlers = D_801EEC4C;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);
}

MATCH void func_801EFD90(void) {
    BattleEffect* slot;
    PartyMember*  work;
    u32           index;
    u8            active;
    u8            i;
    u16*          dst;
    u16*          src;
    PartyMember*  actor;

    g_Task->facing       = g_BattleEffectBattler->facing;
    actor                = g_BattleEffectBattler;
    work                 = g_Task;
    work->pos.x.fixed    = actor->pos.x.fixed;
    work->pos.y.fixed    = actor->pos.y.fixed;
    work->pos.z.fixed    = actor->pos.z.fixed;
    g_Task->unk_04       = func_801F0230();
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    Battle_SelectActiveBattlerScript(0xC, 2);
    BMAGIC_ALLOC_BATTLER_EFFECT();
    work                                            = g_Task;
    g_BattleEffects[index & BYTE_MASK].header.mode  = 2;
    g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
    g_BattleEffects[index & BYTE_MASK].header.step  = 0;
    g_BattleEffects[index & BYTE_MASK].step_index   = 31;
    g_BattleEffects[index & BYTE_MASK].target.party = work;
    g_Task->param.unk_0B += 1;
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < 16; i++) {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
    }
    g_GfxPalettePending = 1;
}

MATCH void func_801F0018(void) {
    PartyMember* actor;
    PartyMember* work;
    u8           slot;

    if (g_Task->param.unk_0B != 0) {
        return;
    }
    if (g_Task->unk_04 != 0xFF) {
        actor               = g_Battle.selected_actor;
        g_Task->pos.x.fixed = actor->pos.x.fixed;
        g_Task->pos.y.fixed = actor->pos.y.fixed;
        g_Task->pos.z.fixed = actor->pos.z.fixed;
        if (Battle_CanTarget(D_800B6BF0[g_Task->unk_04 & 3], g_Battle.target_selector) & BYTE_MASK) {
            slot                               = Battle_AllocEffect(1, 72);
            g_BattleEffects[slot].target.party = g_Task;
            g_BattleEffects[slot].unk_04       = g_Task->unk_04;
            g_BattleEffects[slot].arg.unk_09   = 21;
            g_BattleEffects[slot].unk_0A       = 8;
            g_Task->param.unk_0B++;
        } else {
            slot                               = Battle_AllocEffect(1, 72) & BYTE_MASK;
            work                               = g_Task;
            g_BattleEffects[slot].unk_04       = 8;
            g_BattleEffects[slot].arg.unk_09   = 21;
            g_BattleEffects[slot].unk_0A       = 8;
            g_BattleEffects[slot].target.party = work;
            g_Task->param.unk_0B++;
        }
    }
    Battle_SelectActiveBattlerScript(4, 0);
    g_BattleEffectBattler->header.flags &= 0xBF;
    g_Task->header.mode++;
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

MATCH u32 func_801F0230(void) {
    return LOHU(g_Battle.action_id) == 7 ? 7 : 0xFF;
}

/* func_801F0250 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801F0294(void) {
    BMagicEffectSteps handlers;

    handlers = D_801EEC58;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Area_AddGridActor();
    }
}

MATCH void func_801F0330(void) {
    g_Task->scale.x = 0x10000;
    g_Task->scale.y = 0x10000;
    g_Task->unk_48  = 2;
    g_Task->unk_09  = 0x1E;
    g_Task->header.step += 1;
}

MATCH void func_801F037C(void) {
    PartyMember* work = g_Task;
    u8           timer;

    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    work->scale.x += 0x400;
    work->scale.y += 0x800;
    if (timer == 0) {
        g_Task->unk_09 = func_800AFF98();
        g_Task->header.step += 1;
    }
}

MATCH void func_801F03FC(void) {
    u8 counter;

    Actor_StepAnimOnce();
    counter        = g_Task->unk_09 - 1;
    g_Task->unk_09 = counter;
    if (!(counter & BYTE_MASK)) {
        Battle_MarkDamaged(g_Battle.target_selector);
        Battle_PlayActiveBattlerSE(2, 4);
        g_Task->header.step += 1;
    }
}

MATCH void func_801F047C(void) {
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        SND_QueueSelectionSE(0x101);
        g_Task->unk_09 = 0xF;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F04DC(void) {
    Actor* work;
    u8     timer;

    work          = g_Task;
    timer         = work->timer - 1;
    work->timer   = timer;
    work->scale.x = work->scale.x - 0x800;
    work->scale.y = work->scale.y - 0x1000;
    if (timer == 0) {
        g_BattleEffectBattler->param.unk_0B = 0xFF;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0548(void) {
    Effect_Reset();
}

MATCH void func_801F0568(void) {
    Magic008ThirdSteps handlers;

    handlers = D_801EEC70;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Area_AddGridActor();
    }
}

#ifdef NON_MATCHING
NON_MATCHING void func_801F05FC(void) {
    PartyMember* work;
    s8           tint;

    g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    g_Task->unk_5C    = 1;
    g_Task->unk_2B    = 1;
    tint              = -0x80;
    g_Task->unk_5D    = tint;
    g_Task->unk_5E    = tint;
    g_Task->unk_5F    = tint;
    work              = g_Task;
    work->pos.x.fixed = g_AreaScrollTargetX;
    work->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    work->pos.y.fixed = g_AreaScrollTargetY;
    work->unk_48      = 2;
    work->scale.x     = 0x18000;
    work->scale.y     = 0x28000;
    g_Task->unk_27    = g_BattleEffectBattler->unk_27;
    SND_QueueSelectionSE(0x100);
    g_Task->unk_09 = 0x20;
    g_Task->header.step += 1;
}
#else
INCLUDE_ASM(func_801F05FC);
#endif

MATCH void func_801F0710(void) {
    u8 count;

    g_Task->unk_5D += 3;
    g_Task->unk_5E += 3;
    g_Task->unk_5F += 3;
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_Task->unk_09 = func_800AFF98();
        g_Task->header.step += 1;
    }
}

MATCH void func_801F07D4(void) {
    u8 counter;

    Actor_StepAnimOnce();
    counter        = g_Task->unk_09 - 1;
    g_Task->unk_09 = counter;
    if (!(counter & BYTE_MASK)) {
        Battle_MarkDamaged(g_Battle.target_selector);
        Battle_PlayActiveBattlerSE(2, 4);
        g_Task->unk_09 = 0x20;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0864(void) {
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        SND_QueueSelectionSE(0x101);
        g_Task->unk_09 = 0x20;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F08C4(void) {
    u8 counter;

    g_Task->unk_5D -= 3;
    g_Task->unk_5E -= 3;
    g_Task->unk_5F -= 3;
    counter        = g_Task->unk_09 - 1;
    g_Task->unk_09 = counter;
    if (!(counter & BYTE_MASK)) {
        BATTLE_ACTIVE_WORK->param.unk_0B = 0xFF;
        Effect_Reset();
    }
}

MATCH void func_801F0964(void) {
    Magic008FirstSteps handlers;

    handlers = D_801EEC84;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
}

MATCH void func_801F09D0(void) {
    g_Task->unk_09      = func_800AFF98();
    g_Task->header.step = g_Task->header.step + 1;
    Area_AddGridActor();
}

MATCH void func_801F0A20(void) {
    u8 value;

    value          = g_Task->unk_09 - 1;
    g_Task->unk_09 = value;
    if (!(value & BYTE_MASK)) {
        Actor_StepAnimOnce();
        Battle_PlayActiveBattlerSE(2, 4);
        g_Task->header.step += 1;
    } else if (Actor_StepAnimOnce() & BYTE_MASK) {
        Battle_PlayActiveBattlerSE(2, 4);
        g_Task->unk_09 = 0;
        g_Task->header.step += 1;
    }
    Area_AddGridActor();
}

MATCH void func_801F0AC8(void) {
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        Battle_MarkDamaged(g_Battle.target_selector);
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        g_Task->header.step += 1;
    }
    Area_AddGridActor();
}

MATCH void func_801F0B44(void) {
    if (g_Task->unk_09 < 0xCU) {
        if (g_Battle.action_id != 0xA4) {
            Effect_DrawScreenFade();
        }
        g_Task->unk_09 += 4;
        return;
    }
    Effect_Reset();
}

#include "overlays/bmagic/shared/Effect_DrawScreenFade.h"

MATCH void func_801F0DA8(void) {
    BMagicEffectSteps handlers;

    handlers = D_801EEC94;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Area_AddGridActor();
    }
}

MATCH void func_801F0E54(void) {
    s8 tint;

    g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    g_Task->unk_5C      = 1;
    g_Task->unk_2B      = 1;
    tint                = -0x50;
    g_Task->unk_5D      = tint;
    g_Task->unk_5E      = tint;
    g_Task->unk_5F      = tint;
    g_Task->unk_27      = g_BattleEffectBattler->unk_27;
    g_Task->facing      = g_BattleEffectBattler->facing;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    g_Task->unk_0C      = D_801F1C04[g_Task->param.unk_0B].x;
    g_Task->unk_10      = D_801F1C04[g_Task->param.unk_0B].y;
    Effect_RotatePosition(g_Task);
    g_Task->unk_09 = func_800AFF98();
    g_Task->header.step += 1;
}

MATCH void func_801F0FA4(void) {
    u8 value;

    if (g_FrameCount & 0x1) {
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        Actor_StepAnimOnce();
        value          = g_Task->unk_09 - 1;
        g_Task->unk_09 = value;
        if (!(value & BYTE_MASK)) {
            g_Task->unk_09 = g_Task->param.unk_0B + 4;
            g_Task->header.step += 1;
        }
    } else {
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + g_Task->unk_0C;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + g_Task->unk_10;
    }
}

MATCH void func_801F1090(void) {
    u8 value;

    if (g_FrameCount & 0x1) {
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        value               = g_Task->unk_09 - 1;
        g_Task->unk_09      = value;
        if (!(value & BYTE_MASK)) {
            if (g_Task->param.unk_0B == 0) {
                Battle_PlayActiveBattlerSE(2, 4);
                Battle_MarkDamaged(g_BattleTargetSelector);
            }
            g_Task->header.step += 1;
        }
    } else {
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + g_Task->unk_0C;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + g_Task->unk_10;
    }
}

MATCH void func_801F117C(void) {
    if ((Actor_StepAnimOnce() & BYTE_MASK) != 0u) {
        g_Task->header.step += 1u;
    }
}

MATCH void func_801F11C4(void) {
    g_Task->unk_5D -= 3;
    g_Task->unk_5E -= 3;
    g_Task->unk_5F -= 3;
    if ((s8)g_Task->unk_5D == -0x80) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F1274(void) {
    Effect_Reset();
}

MATCH void func_801F1294(void) {
    Magic008EarlySteps handlers;

    handlers = D_801EECAC;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Area_AddGridActor();
    }
}

#include "overlays/bmagic/shared/Effect_SetDuration.h"

MATCH void func_801F1384(void) {
    u8 timer;

    Actor_StepAnimOnce();
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        Battle_PlayActiveBattlerSE(2, 0);
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Task->header.step += 1;
    }
}

MATCH void func_801F1400(void) {
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        if (g_Task->header.step == 5) {
            g_BattleEffectBattler->param.unk_0B = 0xFF;
        }
        g_Task->header.step += 1;
    }
}

MATCH void func_801F1474(void) {
    /* FAKE: retail reserves 16 bytes of frame that no statement uses; pure C differs only in that frame. */
    FAKE_STACK_PADS(u8, 16);
    u8 count;

    MAGIC008_HIT_OR_ABORT(6);
}

MATCH void func_801F16E8(void) {
    Effect_Reset();
}

MATCH void func_801F1708(void) {
    Magic008Steps handlers;

    handlers = D_801EECC8;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Area_AddGridActor();
    }
}

MATCH void Effect_ReloadTimerAndStep2(void) {
    BMAGIC_RELOAD_TIMER_AND_STEP();
}

MATCH void func_801F1804(void) {
    u8 timer;

    Actor_StepAnimOnce();
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        Battle_PlayActiveBattlerSE(2, 0);
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Task->header.step += 1;
    }
}

MATCH void func_801F1880(void) {
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        if (g_Task->header.step == 8) {
            g_BattleEffectBattler->param.unk_0B = 0xFF;
        }
        g_Task->header.step += 1;
    }
}

MATCH void func_801F18F4(void) {
    /* FAKE: retail reserves 16 bytes of frame that no statement uses; pure C differs only in that frame. */
    FAKE_STACK_PADS(u8, 16);
    u8 count;

    MAGIC008_HIT_OR_ABORT(9);
    if (g_Task->header.step != 9 && g_Battle.action_id == 11 && (rand() & 7) == 0) {
        g_BattleEffectBattler->param.unk_0B = 0xFF;
        g_Task->header.step                 = 9;
    }
}

MATCH void func_801F1BCC(void) {
    Effect_Reset();
}
