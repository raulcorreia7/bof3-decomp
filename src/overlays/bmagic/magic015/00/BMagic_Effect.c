#include "magic015_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EECA0 */
MATCH void BMagic_ChargeUpdate(void) {
    Magic015Steps table = g_BMagicChargeTaskModes;

    SYS_DISPATCH_TASK(table.steps, 1, g_Self);
}

#include "overlays/bmagic/shared/Effect_CopyActiveBattlerToSlot.h"

/* func_801EED0C */
MATCH void BMagic_ChargeInit(void) {
    PartyMember* work;
    u32          index;
    PartyMember* owner;
    u8           i;

    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&SELF(PartyMember)->pos, &g_BattleEffectBattler->pos);
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->header.mode += 1;
    Battle_SelectActiveBattlerScript(8, 2);
    for (i = 0; i < 4; i++) {
        index = Battle_AllocEffect(1, BMAGIC_EFFECT_CHARGE_FLYING_KICK);
        Effect_CopyActiveBattlerToSlot(index);
        work                                            = SELF(PartyMember);
        g_BattleEffects[index & BYTE_MASK].effect_type  = BMAGIC_EFFECT_CHARGE_FLYING_KICK;
        g_BattleEffects[index & BYTE_MASK].header.mode  = BMAGIC_CHARGE_EFFECT_TRAIL;
        g_BattleEffects[index & BYTE_MASK].header.step  = 0;
        g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
        g_BattleEffects[index & BYTE_MASK].arg.unk_09   = (i ^ 3) + 1;
        g_BattleEffects[index & BYTE_MASK].unk_0B       = i ^ 3;
        g_BattleEffects[index & BYTE_MASK].target.party = work;
        SELF(PartyMember)->param.unk_0B++;
    }
    index = Battle_AllocEffect(1, BMAGIC_EFFECT_CHARGE_FLYING_KICK);
    Effect_CopyActiveBattlerToSlot(index);
    owner                                           = SELF(PartyMember);
    g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
    g_BattleEffects[index & BYTE_MASK].header.mode  = BMAGIC_CHARGE_EFFECT_LEAD;
    g_BattleEffects[index & BYTE_MASK].header.step  = 0;
    g_BattleEffects[index & BYTE_MASK].effect_type  = BMAGIC_EFFECT_CHARGE_FLYING_KICK;
    g_BattleEffects[index & BYTE_MASK].target.party = owner;
    SELF(PartyMember)->param.unk_0B++;
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
    SELF(PartyMember)->unk_27 = Battle_CopyCellPalette(g_BattleEffectBattler);
    SELF(PartyMember)->unk_28 = g_BattleEffectBattler->unk_28;
    SELF(PartyMember)->unk_24 = g_BattleEffectBattler->unk_24;
    Battle_SetCellPaletteStp(SELF(PartyMember));
}

#include "overlays/bmagic/shared/Effect_RestorePaletteAndReleaseActive.h"

/* func_801EF150 */
MATCH void BMagic_ChargeEnd(void) {
    EFFECT_RESTORE_PALETTE_AND_RELEASE_ACTIVE();
}

#include "shared/Effect_StartPlaying.h"

#include "shared/Effect_PlayOnce.h"

MATCH void func_801EF248(void) {
    Magic015Steps table = D_801EEC14;

    SYS_DISPATCH_TASK(table.steps, 1, g_Self);
}

MATCH void func_801EF2B4(void) {
    PartyMember* work;
    u32          index;
    u8           i;

    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&SELF(PartyMember)->pos, &g_BattleEffectBattler->pos);
    SELF(PartyMember)->unk_27 = Battle_CopyCellPalette(g_BattleEffectBattler);
    SELF(PartyMember)->unk_28 = g_BattleEffectBattler->unk_28;
    SELF(PartyMember)->unk_24 = g_BattleEffectBattler->unk_24;
    Battle_SetCellPaletteStp(SELF(PartyMember));
    Battle_ClearCellPaletteEntry(SELF(PartyMember));
    Battle_SelectActiveBattlerScript(8, 2);
    SELF(PartyMember)->param.unk_0B = 0;
    for (i = 0; i < 3; i++) {
        index = Battle_AllocEffect(1, BMAGIC_EFFECT_CHARGE_FLYING_KICK);
        Effect_CopyActiveBattlerToSlot(index);
        work                                            = SELF(PartyMember);
        g_BattleEffects[index & BYTE_MASK].header.mode  = 2;
        g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
        g_BattleEffects[index & BYTE_MASK].effect_type  = BMAGIC_EFFECT_CHARGE_FLYING_KICK;
        g_BattleEffects[index & BYTE_MASK].header.step  = 0;
        g_BattleEffects[index & BYTE_MASK].unk_0B       = i;
        g_BattleEffects[index & BYTE_MASK].arg.unk_09   = i * 2 + 1;
        g_BattleEffects[index & BYTE_MASK].target.party = work;
        SELF(PartyMember)->param.unk_0B++;
    }
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x00));
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
    SELF(PartyMember)->header.mode++;
}

MATCH void func_801EF594(void) {
    EFFECT_RESTORE_PALETTE_AND_RELEASE_ACTIVE();
}

MATCH void Effect_StartPlaying2(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}

/* func_801EF644 */
MATCH void BMagic_FlyingKickUpdate(void) {
    Magic015Steps table = g_BMagicFlyingKickTaskModes;

    SYS_DISPATCH_TASK(table.steps, 1, g_Self);
}

/* func_801EF6B0 */
MATCH void BMagic_FlyingKickInit(void) {
    PartyMember* work;
    u32          index;

    SELF(PartyMember)->facing             = g_BattleEffectBattler->facing;
    SELF(PartyMember)->pos.x.fixed        = g_BattleEffectBattler->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed        = g_BattleEffectBattler->pos.y.fixed;
    SELF(PartyMember)->pos.z.part.integer = g_BattleEffectBattler->pos.z.part.integer;
    SELF(PartyMember)->param.unk_0B       = 1;
    Battle_SelectActiveBattlerScript(8, 0);
    index = Battle_AllocEffect(1, BMAGIC_EFFECT_CHARGE_FLYING_KICK);
    Effect_CopyActiveBattlerToSlot(index);
    work                                            = SELF(PartyMember);
    g_BattleEffects[index & BYTE_MASK].header.mode  = BMAGIC_FLYING_KICK_EFFECT_IMAGE;
    g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
    g_BattleEffects[index & BYTE_MASK].header.step  = 0;
    g_BattleEffects[index & BYTE_MASK].effect_type  = BMAGIC_EFFECT_CHARGE_FLYING_KICK;
    g_BattleEffects[index & BYTE_MASK].arg.unk_09   = 0;
    g_BattleEffects[index & BYTE_MASK].target.party = work;
    SELF(PartyMember)->unk_27                       = Battle_CopyCellPalette(g_BattleEffectBattler);
    SELF(PartyMember)->unk_28                       = g_BattleEffectBattler->unk_28;
    SELF(PartyMember)->unk_24                       = g_BattleEffectBattler->unk_24;
    Battle_SetCellPaletteStp(SELF(PartyMember));
    Battle_ClearCellPaletteEntry(SELF(PartyMember));
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
    SELF(PartyMember)->header.mode++;
}

/* func_801EF93C */
MATCH void BMagic_FlyingKickEnd(void) {
    if (SELF(PartyMember)->param.unk_0B == 0) {
        func_800AFC54();
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        Battle_SelectActiveBattlerScript(4, 0);
        SELF(PartyMember)->header.mode += 1;
    }
}

MATCH void Effect_StartPlaying4(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}

/* func_801EF9E4 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

/* func_801EFA28 */
MATCH void BMagic_ChargeLeadUpdate(void) {
    Magic015SecondSteps handlers = g_BMagicChargeLeadSteps;

    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Area_AddGridActor();
    }
}

/* func_801EFAE4 */
MATCH void BMagic_ChargeLeadStart(void) {
    if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
        SELF(PartyMember)->header.step += 1;
    } else {
        SELF(PartyMember)->header.step += 2;
    }
    SELF(PartyMember)->unk_27      = g_BattleEffectBattler->unk_27;
    SELF(PartyMember)->unk_2B      = 1;
    SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
}

/* func_801EFB90 */
MATCH void BMagic_ChargeLeadWaitAnim(void) {
    if ((Script_AnimStepOnce() & BYTE_MASK) != 0u) {
        SELF(PartyMember)->header.step += 1u;
    }
}

/* func_801EFBD8 */
MATCH void BMagic_ChargeLeadStrike(void) {
    PartyMember** actor_cell;
    PartyMember*  record;
    PartyMember*  work;
    s32           heading;

    actor_cell = &g_Battle.selected_actor;
    func_800AF2B4((BattleRange*)*actor_cell, 0x60);
    if (func_800AF66C((BattleRange*)*actor_cell, 0xC000) != 0) {
        if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
            Battle_PlayActiveBattlerSE(2, 0);
        }
        SND_SEQueueSelection(EMI_SE_ID(SND_BANK_AREA, 0x03));
        Battle_MarkDamaged(g_Battle.target_selector);
        record       = SELF(PartyMember);
        heading      = ratan2(g_BattleEffectBattler->pos.x.fixed - record->pos.x.fixed, g_BattleEffectBattler->pos.y.fixed - record->pos.y.fixed);
        work         = SELF(PartyMember);
        work->unk_0C = heading;
        work->unk_14 = 0x40;
        work->unk_09 = 0x10;
        work->unk_20 = -8;
        SELF(PartyMember)->header.step++;
    }
}

/* func_801EFCC4 */
MATCH void BMagic_ChargeLeadReturn(void) {
    PartyMember* work;
    s32          dz;
    u8           timer;

    SELF(PartyMember)->pos.x.fixed += FIXED_MUL(rsin(SELF(PartyMember)->unk_0C), 0x2000);
    SELF(PartyMember)->pos.y.fixed += FIXED_MUL(rcos(SELF(PartyMember)->unk_0C), 0x2000);
    work                     = SELF(PartyMember);
    dz                       = work->unk_14 + work->unk_20;
    timer                    = work->unk_09 - 1;
    work->unk_09             = timer;
    work->unk_14             = dz;
    work->pos.z.part.integer = (u16)work->pos.z.part.integer + dz;
    if (timer == 0) {
        SELF(PartyMember)->header.step += 1;
    }
}

/* func_801EFD7C */
MATCH void BMagic_ChargeLeadWaitTrail(void) {
    if (g_BattleEffectBattler->param.unk_0B == 1) {
        SELF(PartyMember)->scale.x = 0x10000;
        SELF(PartyMember)->scale.y = 0x10000;
        SELF(PartyMember)->unk_48  = 2;
        SELF(PartyMember)->unk_09  = 8;
        SELF(PartyMember)->header.step += 1;
    }
}

/* func_801EFDE8 */
MATCH void BMagic_ChargeLeadStretch(void) {
    u8 timer;

    timer = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->scale.x -= 0x2000;
    SELF(PartyMember)->scale.y += 0x3000;
    SELF(PartyMember)->pos.z.part.integer = (u16)SELF(PartyMember)->pos.z.part.integer + 0x20;
    SELF(PartyMember)->unk_09             = timer;
    if (timer == 0) {
        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        SELF(PartyMember)->unk_09      = 8;
        SELF(PartyMember)->header.step += 1;
    }
}

/* func_801EFE84 */
MATCH void BMagic_ChargeLeadRestore(void) {
    PartyMember* work = SELF(PartyMember);
    u8           timer;

    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    work->scale.x += 0x2000;
    work->scale.y -= 0x3000;
    if (timer == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        SELF(PartyMember)->header.step += 1;
    }
}

/* func_801EFEFC */
MATCH void BMagic_ChargeLeadEnd(void) {
    Effect_Reset();
}

/* func_801EFF1C */
MATCH void BMagic_ChargeTrailUpdate(void) {
    Magic015ThirdSteps handlers;

    handlers = g_BMagicChargeTrailSteps;
    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Area_AddGridActor();
    }
}

/* func_801EFFC0 */
MATCH void BMagic_ChargeTrailStart(void) {
    u8 timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        SELF(PartyMember)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        SELF(PartyMember)->unk_5C = 1;
        SELF(PartyMember)->unk_5D = (u8) - ((SELF(PartyMember)->param.unk_0B + 1) * 0x14);
        SELF(PartyMember)->unk_5E = (u8) - ((SELF(PartyMember)->param.unk_0B + 1) * 0x14);
        SELF(PartyMember)->unk_5F = (u8) - ((SELF(PartyMember)->param.unk_0B + 1) * 0x14);
        SELF(PartyMember)->unk_2B = 0;
        SELF(PartyMember)->unk_27 = g_BattleEffectBattler->unk_27;
        if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
            SELF(PartyMember)->header.step += 1;
        } else {
            SELF(PartyMember)->header.step += 2;
        }
        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    }
}

/* func_801F014C */
MATCH void BMagic_ChargeTrailWaitAnim(void) {
    if ((Script_AnimStepOnce() & BYTE_MASK) != 0u) {
        SELF(PartyMember)->header.step += 1u;
    }
}

/* func_801F0194 */
MATCH void BMagic_ChargeTrailApproach(void) {
    PartyMember** selected;
    PartyMember*  work;

    selected = &g_Battle.selected_actor;
    func_800AF2B4((BattleRange*)*selected, 0x60);
    if (func_800AF66C((BattleRange*)*selected, 0xC000) != 0) {
        SELF(PartyMember)->unk_0C = ratan2(g_BattleEffectBattler->pos.x.fixed - SELF(PartyMember)->pos.x.fixed, g_BattleEffectBattler->pos.y.fixed - SELF(PartyMember)->pos.y.fixed);
        work                      = SELF(PartyMember);
        work->unk_14              = 0x40;
        work->unk_09              = 0x10;
        work->unk_20              = -8;
        SELF(PartyMember)->header.step += 1;
    }
}

/* func_801F0248 */
MATCH void BMagic_ChargeTrailReturn(void) {
    u8 timer;

    SELF(PartyMember)->pos.x.fixed += FIXED_MUL(rsin(SELF(PartyMember)->unk_0C), 0x2000);
    SELF(PartyMember)->pos.y.fixed += FIXED_MUL(rcos(SELF(PartyMember)->unk_0C), 0x2000);
    SELF(PartyMember)->unk_14 += SELF(PartyMember)->unk_20;
    SELF(PartyMember)->pos.z.part.integer = (u16)SELF(PartyMember)->pos.z.part.integer + SELF(PartyMember)->unk_14;
    timer                                 = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09             = timer;
    if (timer == 0) {
        SELF(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_TickDownAndClear.h"

MATCH void func_801F0334(void) {
    Callback handlers[7];

    __builtin_memcpy(handlers, D_801EEC68, sizeof(handlers));
    SYS_DISPATCH_BYTE(handlers, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Area_AddGridActor();
        if (SELF(PartyMember)->unk_09 != 0 && SELF(PartyMember)->param.unk_0B == 0 && SELF(PartyMember)->header.step < 5) {
            if (SELF(PartyMember)->header.step < 4) {
                BMagic_PushGroundMatrix();
            } else {
                BMagic_PushTargetMatrix();
            }
            BMagic_DrawShadow();
            PopMatrix();
        }
    }
}

MATCH void func_801F045C(void) {
    PartyMember* task;
    s8           tint;
    u8           timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        SELF(PartyMember)->unk_27 = g_BattleEffectBattler->unk_27;
        SELF(PartyMember)->unk_2B = SELF(PartyMember)->param.unk_0B == 0;
        if (SELF(PartyMember)->param.unk_0B != 0) {
            SELF(PartyMember)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
            SELF(PartyMember)->unk_5C = 1;
            task                      = SELF(PartyMember);
            tint                      = -0x40;
            task->unk_5F              = tint;
            task->unk_5E              = tint;
            task->unk_5D              = tint;
        }
        task                      = SELF(PartyMember);
        task->unk_14              = 0x80;
        task->unk_20              = -2;
        task->scale.x             = 0x10000;
        task->scale.y             = 0x10000;
        task->unk_48              = 2;
        SELF(PartyMember)->unk_09 = 0x10;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F0570(void) {
    PartyMember** selected;
    PartyMember*  work;
    s32           dz;
    u8            timer;

    selected = &g_Battle.selected_actor;
    func_800AF4A0((BattleRange*)*selected, 0x1800, 0);
    work                     = SELF(PartyMember);
    timer                    = work->unk_09 - 1;
    dz                       = work->unk_14 + work->unk_20;
    work->unk_14             = dz;
    work->pos.z.part.integer = (u16)work->pos.z.part.integer + dz;
    work->scale.x            = work->scale.x - 0x800;
    work->scale.y            = work->scale.y + 0x1000;
    work->unk_09             = timer;
    if (timer == 0) {
        SELF(PartyMember)->pos.x.fixed        = (*selected)->pos.x.fixed;
        SELF(PartyMember)->pos.y.fixed        = (*selected)->pos.y.fixed;
        SELF(PartyMember)->pos.z.part.integer = (u16)(*selected)->pos.z.part.integer + 0xC00;
        func_800AF4A0((BattleRange*)g_BattleEffectBattler, 0x20000, 0);
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F0654(void) {
    PartyMember* task;
    s8           tint;
    u8           timer;

    timer                     = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 4) {
        task          = SELF(PartyMember);
        task->scale.x = 0x8000;
        task->scale.y = 0x18000;
        if (task->param.unk_0B != 0) {
            task->unk_5D              = -((task->param.unk_0B * 0x10) + 0x30);
            SELF(PartyMember)->unk_5E = -((SELF(PartyMember)->param.unk_0B * 0x10) + 0x40);
            SELF(PartyMember)->unk_5F = -((SELF(PartyMember)->param.unk_0B * 0x10) + 0x40);
        } else {
            SELF(PartyMember)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
            SELF(PartyMember)->unk_5C = 1;
            SELF(PartyMember)->unk_5D = 0x30;
            tint                      = -0x40;
            SELF(PartyMember)->unk_5E = tint;
            SELF(PartyMember)->unk_5F = tint;
        }
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F0770(void) {
    PartyMember* work;
    PartyMember* member;
    PartyMember* flag;
    u8           countdown;

    func_800AF4A0((BattleRange*)g_Battle.selected_actor, 0x2000, 0);
    work                     = SELF(PartyMember);
    countdown                = work->unk_09 + 1;
    work->unk_09             = countdown;
    work->pos.z.part.integer = (u16)work->pos.z.part.integer - 0xC0;
    if (countdown == 0x14) {
        member          = SELF(PartyMember);
        member->unk_48  = 0;
        flag            = SELF(PartyMember);
        member->unk_14  = 0x48;
        member->unk_20  = -8;
        member->scale.x = 0x10000;
        member->scale.y = 0x10000;
        if (flag->param.unk_0B == 0) {
            Battle_MarkDamaged(g_Battle.target_selector);
            if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
                Battle_PlayActiveBattlerSE(2, 0);
            }
            SND_SEQueueSelection(EMI_SE_ID(SND_BANK_AREA, 0x03));
        }
        SELF(PartyMember)->header.step++;
    }
}

MATCH void func_801F0864(void) {
    s32 speed;

    if (SELF(PartyMember)->param.unk_0B != 0) {
        if ((s8)SELF(PartyMember)->unk_5D != -0x80) {
            SELF(PartyMember)->unk_5D -= D_801F1640[SELF(PartyMember)->param.unk_0B - 1][0];
            SELF(PartyMember)->unk_5E -= D_801F1640[SELF(PartyMember)->param.unk_0B - 1][1];
            SELF(PartyMember)->unk_5F -= D_801F1640[SELF(PartyMember)->param.unk_0B - 1][1];
        }
    } else {
        if ((s8)SELF(PartyMember)->unk_5D != 0) {
            SELF(PartyMember)->unk_5D -= 3;
            SELF(PartyMember)->unk_5E += 4;
            SELF(PartyMember)->unk_5F += 4;
        }
    }
    if (SELF(PartyMember)->unk_09 != 16) {
        SELF(PartyMember)->unk_09--;
    }
    Script_AnimStepOnce();
    func_800AF4A0(g_BattleActiveActor, 0x2000, 0);
    speed                                 = SELF(PartyMember)->unk_14 + SELF(PartyMember)->unk_20;
    SELF(PartyMember)->unk_14             = speed;
    SELF(PartyMember)->pos.z.part.integer = (u16)SELF(PartyMember)->pos.z.part.integer + speed;
    if ((SELF(PartyMember)->unk_14 < 0) && (SELF(PartyMember)->pos.z.fixed < g_Battle.selected_actor->pos.z.fixed)) {
        if (SELF(PartyMember)->param.unk_0B != 0) {
            g_BattleEffectBattler->param.unk_0B--;
            Effect_Reset();
        } else {
            SELF(PartyMember)->unk_5D      = 0;
            SELF(PartyMember)->unk_5E      = 0;
            SELF(PartyMember)->unk_5F      = 0;
            SELF(PartyMember)->pos.z.fixed = g_Battle.selected_actor->pos.z.fixed;
            SELF(PartyMember)->header.step++;
        }
    }
}

MATCH void func_801F0A94(void) {
    s8 tint;

    EFFECT_APPEAR_AT_BATTLER();
}

#include "overlays/bmagic/shared/Effect_RampTintAndFinish.h"

MATCH void func_801F0B8C(void) {
    EFFECT_RAMP_TINT_AND_FINISH();
}

/* func_801F0C30 */
MATCH void BMagic_FlyingKickImageUpdate(void) {
    Callback handlers[7];

    __builtin_memcpy(handlers, g_BMagicFlyingKickImageSteps, sizeof(handlers));
    SYS_DISPATCH_BYTE(handlers, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Area_AddGridActor();
        if (SELF(PartyMember)->unk_09 != 0 && SELF(PartyMember)->header.step < 4) {
            if (SELF(PartyMember)->header.step < 3) {
                BMagic_PushGroundMatrix();
            } else {
                BMagic_PushTargetMatrix();
            }
            BMagic_DrawShadow();
            PopMatrix();
        }
    }
}

/* func_801F0D48 */
MATCH void BMagic_FlyingKickImageStart(void) {
    SELF(PartyMember)->unk_14 = 0x80;
    SELF(PartyMember)->unk_20 = -0x10;
    SELF(PartyMember)->unk_27 = BATTLE_ACTIVE_WORK->unk_27;
    SELF(PartyMember)->unk_09 = 0x14;
    SELF(PartyMember)->timer  = 7;
    SELF(PartyMember)->header.step += 1;
}

/* func_801F0DB4 */
MATCH void BMagic_FlyingKickImageRise(void) {
    PartyMember* work;
    s32          dz;
    u8           timer;
    func_800AF4A0((BattleRange*)g_BattleSelectedActor, 0x3800, 0);
    work = SELF(PartyMember);
    dz   = work->unk_14 + work->unk_20;
    work->unk_09 -= 1;
    work->unk_14             = dz;
    work->pos.z.part.integer = (u16)work->pos.z.part.integer + dz;
    timer                    = SELF(PartyMember)->timer - 1;
    SELF(PartyMember)->timer = timer;
    if (timer == 0) {
        SELF(PartyMember)->header.step += 1;
    }
}

/* func_801F0E54 */
MATCH void BMagic_FlyingKickImageStrike(void) {
    PartyMember** selected;
    u8            count;

    selected = &g_Battle.selected_actor;
    func_800AF2B4((BattleRange*)*selected, 0x60);
    count = SELF(PartyMember)->unk_09;
    if (count < 20) {
        SELF(PartyMember)->unk_09 = count + 1;
    }
    if (func_800AF5FC((BattleRange*)*selected, 0xC000) != 0) {
        SELF(PartyMember)->unk_14 = 0x48;
        SELF(PartyMember)->unk_20 = -8;
        func_800A9820(g_Battle.target_selector);
        if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
            Battle_PlayActiveBattlerSE(2, 0);
        }
        SND_SEQueueSelection(EMI_SE_ID(SND_BANK_AREA, 0x03));
        SELF(PartyMember)->header.step += 1;
    }
}

/* func_801F0F2C */
MATCH void BMagic_FlyingKickImageFall(void) {
    s32 speed;
    u8  timer;

    Script_AnimStepOnce();
    func_800AF4A0(g_BattleActiveActor, 0x2000, 0);
    speed                                 = SELF(PartyMember)->unk_14 + SELF(PartyMember)->unk_20;
    SELF(PartyMember)->unk_14             = speed;
    SELF(PartyMember)->pos.z.part.integer = (u16)SELF(PartyMember)->pos.z.part.integer + speed;
    if (SELF(PartyMember)->unk_14 < 0) {
        timer = SELF(PartyMember)->unk_09;
        if (timer < 20) {
            SELF(PartyMember)->unk_09 = timer + 1;
        }
    } else if (g_FrameCount & 0x1) {
        SELF(PartyMember)->unk_09 -= 1;
    }
    if ((SELF(PartyMember)->unk_14 < 0) && (SELF(PartyMember)->pos.z.fixed < g_Battle.selected_actor->pos.z.fixed)) {
        SELF(PartyMember)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        SELF(PartyMember)->unk_5C      = 1;
        SELF(PartyMember)->unk_5D      = 0;
        SELF(PartyMember)->unk_5E      = 0;
        SELF(PartyMember)->unk_5F      = 0;
        SELF(PartyMember)->pos.z.fixed = g_Battle.selected_actor->pos.z.fixed;
        SELF(PartyMember)->header.step++;
    }
}

/* func_801F1088 */
MATCH void BMagic_FlyingKickImageRejoin(void) {
    s8 tint;

    EFFECT_APPEAR_AT_BATTLER();
}

/* func_801F1180 */
MATCH void BMagic_FlyingKickImageFade(void) {
    SELF(PartyMember)->unk_5D += 0x10;
    SELF(PartyMember)->unk_5E += 0x10;
    SELF(PartyMember)->unk_5F += 0x10;
    if ((s8)SELF(PartyMember)->unk_5D == -0x40) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        SELF(PartyMember)->header.step += 1;
    }
}

/* func_801F1230 */
MATCH void BMagic_FlyingKickImageEnd(void) {
    Effect_Reset();
}

/* func_801F1250 */
MATCH void BMagic_PushGroundMatrix(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;
    s16     height;

    PushMatrix();
    rot.vz = 0;
    rot.vy = 0;
    rot.vx = 0;
    pos.vx = (SELF(PartyMember)->pos.x.fixed >> 9) - AREA_CELL_ORIGIN;
    pos.vy = (SELF(PartyMember)->pos.y.fixed >> 9) - AREA_CELL_ORIGIN;
    height = Area_HeightSample(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed);
    pos.vz = -height / 2;
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}

/* func_801F131C */
MATCH void BMagic_PushTargetMatrix(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vz = 0;
    rot.vy = 0;
    rot.vx = 0;
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Battle.selected_actor);
}

/* func_801F13D4 */
MATCH void BMagic_DrawShadow(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_09 << 2;
    g_ScratchPadVectors[2].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[2].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);

    for (i = 1; i <= 8; i++) {
        prim                      = GFX_BeginPolyG3(1);
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = 0;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy;
        setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[0]), 0);
        g_ScratchPadVectors[1].vz = 0;
        g_ScratchPadVectors[0].vz = 0;
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, 128, 128, 128);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}
