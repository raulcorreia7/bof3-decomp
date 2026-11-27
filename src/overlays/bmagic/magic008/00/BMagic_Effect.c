#include "magic008_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EECF0(void) {
    Magic008FirstSteps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Self);
}

MATCH void func_801EED5C(void) {
    BattleEffect* slot;
    PartyMember*  work;
    u32           index;
    u8            active;

    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&SELF(PartyMember)->pos, &g_BattleEffectBattler->pos);
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->header.mode += 1;
    Battle_SelectActiveBattlerScript(0xC, 2);
    BMAGIC_ALLOC_BATTLER_EFFECT();
    work                                            = SELF(PartyMember);
    g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
    g_BattleEffects[index & BYTE_MASK].header.mode  = 0;
    g_BattleEffects[index & BYTE_MASK].header.step  = 0;
    g_BattleEffects[index & BYTE_MASK].effect_type  = BMAGIC_EFFECT_SKILL_STRIKE;
    g_BattleEffects[index & BYTE_MASK].target.party = work;
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
    SND_SEQueueSelection(0x100);
}

MATCH void func_801EEF6C(void) {
    if (SELF(PartyMember)->param.unk_0B == 0xFF) {
        Battle_SelectActiveBattlerScript(4, 0);
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        SELF(PartyMember)->header.mode += 1;
    }
}

#include "shared/Effect_StartPlaying.h"

#include "shared/Effect_PlayOnce.h"

MATCH void func_801EF058(void) {
    Magic008SecondSteps handlers;

    handlers = D_801EEC14;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Self);
}

MATCH void func_801EF0B8(void) {
    BattleEffect* slot;
    PartyMember*  work;
    u32           index;
    u8            active;

    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&SELF(PartyMember)->pos, &g_BattleEffectBattler->pos);
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->header.mode += 1;
    Battle_SelectActiveBattlerScript(0xC, 2);
    BMAGIC_ALLOC_BATTLER_EFFECT();
    work                                            = SELF(PartyMember);
    g_BattleEffects[index & BYTE_MASK].header.mode  = 1;
    g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
    g_BattleEffects[index & BYTE_MASK].header.step  = 0;
    g_BattleEffects[index & BYTE_MASK].effect_type  = BMAGIC_EFFECT_SKILL_STRIKE;
    g_BattleEffects[index & BYTE_MASK].target.party = work;
    SELF(PartyMember)->unk_27                       = Battle_CopyCellPalette(g_BattleEffectBattler);
    SELF(PartyMember)->unk_28                       = g_BattleEffectBattler->unk_28;
    SELF(PartyMember)->unk_24                       = g_BattleEffectBattler->unk_24;
    Battle_SetCellPaletteStp(SELF(PartyMember));
    Battle_ClearCellPaletteEntry(SELF(PartyMember));
}

MATCH void func_801EF324(void) {
    u16* battle_flags;

    if (SELF(PartyMember)->param.unk_0B == 0xFF) {
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
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Self);
}

MATCH void func_801EF3F0(void) {
    BattleEffect* slot;
    PartyMember*  work;
    u32           index;
    u8            active;
    u8            i;

    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&SELF(PartyMember)->pos, &g_BattleEffectBattler->pos);
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->header.mode += 1;
    Battle_SelectActiveBattlerScript(0xC, 2);
    for (i = 0; i < 3; i++) {
        BMAGIC_ALLOC_BATTLER_EFFECT();
        work                                            = SELF(PartyMember);
        g_BattleEffects[index & BYTE_MASK].header.mode  = 3;
        g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
        g_BattleEffects[index & BYTE_MASK].header.step  = 0;
        g_BattleEffects[index & BYTE_MASK].effect_type  = BMAGIC_EFFECT_SKILL_STRIKE;
        g_BattleEffects[index & BYTE_MASK].unk_0B       = i;
        g_BattleEffects[index & BYTE_MASK].target.party = work;
        SELF(PartyMember)->param.unk_0B++;
    }
    SELF(PartyMember)->unk_27 = Battle_CopyCellPalette(g_BattleEffectBattler);
    SELF(PartyMember)->unk_28 = g_BattleEffectBattler->unk_28;
    SELF(PartyMember)->unk_24 = g_BattleEffectBattler->unk_24;
    Battle_SetCellPaletteStp(SELF(PartyMember));
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
}

#include "overlays/bmagic/shared/Effect_RestorePaletteAndReleaseActive.h"

/* func_801EF6AC */
MATCH void BMagic_ChargeEnd(void) {
    EFFECT_RESTORE_PALETTE_AND_RELEASE_ACTIVE();
}

MATCH void Effect_StartPlaying3(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}

MATCH void func_801EF75C(void) {
    Magic008FirstSteps handlers;

    handlers = D_801EEC30;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Self);
}

MATCH void func_801EF7C8(void) {
    BattleEffect* slot;
    PartyMember*  work;
    u32           index;
    u8            active;

    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&SELF(PartyMember)->pos, &g_BattleEffectBattler->pos);
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->header.mode += 1;
    Battle_SelectActiveBattlerScript(0xC, 2);
    BMAGIC_ALLOC_BATTLER_EFFECT();
    work                                            = SELF(PartyMember);
    g_BattleEffects[index & BYTE_MASK].header.mode  = 4;
    g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
    g_BattleEffects[index & BYTE_MASK].header.step  = 0;
    g_BattleEffects[index & BYTE_MASK].effect_type  = BMAGIC_EFFECT_SKILL_STRIKE;
    g_BattleEffects[index & BYTE_MASK].target.party = work;
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
}

MATCH void func_801EF9D4(void) {
    MAGIC008_RELEASE_ACTIVE_AT_END();
}

MATCH void Effect_StartPlaying5(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}

MATCH void func_801EFA74(void) {
    Magic008SecondSteps handlers;

    handlers = D_801EEC40;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Self);
}

#include "overlays/bmagic/shared/Effect_CopyActiveBattlerToSlot.h"

MATCH void func_801EFAD4(void) {
    BattleEffect* slot;
    PartyMember*  work;
    u32           index;
    u8            active;

    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->header.mode += 1;
    Battle_SelectActiveBattlerScript(0xC, 2);
    BMAGIC_ALLOC_BATTLER_EFFECT();
    work                                            = SELF(PartyMember);
    g_BattleEffects[index & BYTE_MASK].header.mode  = 5;
    g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
    g_BattleEffects[index & BYTE_MASK].header.step  = 0;
    g_BattleEffects[index & BYTE_MASK].effect_type  = BMAGIC_EFFECT_SKILL_STRIKE;
    g_BattleEffects[index & BYTE_MASK].target.party = work;
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
}

MATCH void func_801EFC90(void) {
    MAGIC008_RELEASE_ACTIVE_AT_END();
}

MATCH void Effect_StartPlaying7(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}

/* func_801EFD30 */
MATCH void BMagic_SkillStrikeUpdate(void) {
    Magic008SecondSteps handlers;

    handlers = g_BMagicSkillStrikeModes;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Self);
}

/* func_801EFD90 */
MATCH void BMagic_SkillStrikeInit(void) {
    BattleEffect* slot;
    PartyMember*  work;
    u32           index;
    u8            active;
    u8            i;
    u16*          dst;
    u16*          src;
    PartyMember*  actor;

    SELF(PartyMember)->facing       = g_BattleEffectBattler->facing;
    actor                           = g_BattleEffectBattler;
    work                            = SELF(PartyMember);
    work->pos.x.fixed               = actor->pos.x.fixed;
    work->pos.y.fixed               = actor->pos.y.fixed;
    work->pos.z.fixed               = actor->pos.z.fixed;
    SELF(PartyMember)->unk_04       = BMagic_SkillStrikeFollowUp();
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->header.mode += 1;
    Battle_SelectActiveBattlerScript(0xC, 2);
    BMAGIC_ALLOC_BATTLER_EFFECT();
    work                                            = SELF(PartyMember);
    g_BattleEffects[index & BYTE_MASK].header.mode  = BMAGIC_SKILL_STRIKE_EFFECT_STRIKE;
    g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
    g_BattleEffects[index & BYTE_MASK].header.step  = 0;
    g_BattleEffects[index & BYTE_MASK].effect_type  = BMAGIC_EFFECT_SKILL_STRIKE;
    g_BattleEffects[index & BYTE_MASK].target.party = work;
    SELF(PartyMember)->param.unk_0B += 1;
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < 16; i++) {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
    }
    g_GfxPalettePending = 1;
}

/* func_801F0018 */
MATCH void BMagic_SkillStrikeSpawnFollowUp(void) {
    PartyMember* actor;
    PartyMember* work;
    u8           slot;

    if (SELF(PartyMember)->param.unk_0B != 0) {
        return;
    }
    if (SELF(PartyMember)->unk_04 != BMAGIC_SKILL_STRIKE_FOLLOW_UP_NONE) {
        actor                          = g_Battle.selected_actor;
        SELF(PartyMember)->pos.x.fixed = actor->pos.x.fixed;
        SELF(PartyMember)->pos.y.fixed = actor->pos.y.fixed;
        SELF(PartyMember)->pos.z.fixed = actor->pos.z.fixed;
        if (Battle_CanTarget(D_800B6BF0[SELF(PartyMember)->unk_04 & 3], g_Battle.target_selector) & BYTE_MASK) {
            slot                               = Battle_AllocEffect(1, 72);
            g_BattleEffects[slot].target.party = SELF(PartyMember);
            g_BattleEffects[slot].unk_04       = SELF(PartyMember)->unk_04;
            g_BattleEffects[slot].arg.unk_09   = 21;
            g_BattleEffects[slot].unk_0A       = 8;
            SELF(PartyMember)->param.unk_0B++;
        } else {
            slot                               = Battle_AllocEffect(1, 72) & BYTE_MASK;
            work                               = SELF(PartyMember);
            g_BattleEffects[slot].unk_04       = 8;
            g_BattleEffects[slot].arg.unk_09   = 21;
            g_BattleEffects[slot].unk_0A       = 8;
            g_BattleEffects[slot].target.party = work;
            SELF(PartyMember)->param.unk_0B++;
        }
    }
    Battle_SelectActiveBattlerScript(4, 0);
    g_BattleEffectBattler->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
    SELF(PartyMember)->header.mode++;
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

/* func_801F0230 */
MATCH u32 BMagic_SkillStrikeFollowUp(void) {
    return LOHU(g_Battle.action_id) == ABILITY_MIND_FLAY ? BMAGIC_SKILL_STRIKE_FOLLOW_UP_MIND_FLAY : BMAGIC_SKILL_STRIKE_FOLLOW_UP_NONE;
}

/* func_801F0250 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801F0294(void) {
    BMagicEffectSteps handlers;

    handlers = D_801EEC58;
    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0) {
        Area_AddGridActor();
    }
}

MATCH void func_801F0330(void) {
    SELF(PartyMember)->scale.x = 0x10000;
    SELF(PartyMember)->scale.y = 0x10000;
    SELF(PartyMember)->unk_48  = 2;
    SELF(PartyMember)->unk_09  = 0x1E;
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801F037C(void) {
    PartyMember* work = SELF(PartyMember);
    u8           timer;

    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    work->scale.x += 0x400;
    work->scale.y += 0x800;
    if (timer == 0) {
        SELF(PartyMember)->unk_09 = func_800AFF98();
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F03FC(void) {
    u8 counter;

    Script_AnimStepOnce();
    counter                   = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = counter;
    if (!(counter & BYTE_MASK)) {
        Battle_MarkDamaged(g_Battle.target_selector);
        Battle_PlayActiveBattlerSE(2, 4);
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F047C(void) {
    if (Script_AnimStepOnce() & BYTE_MASK) {
        SND_SEQueueSelection(0x101);
        SELF(PartyMember)->unk_09 = 0xF;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F04DC(void) {
    Actor* work;
    u8     timer;

    work          = SELF(PartyMember);
    timer         = work->timer - 1;
    work->timer   = timer;
    work->scale.x = work->scale.x - 0x800;
    work->scale.y = work->scale.y - 0x1000;
    if (timer == 0) {
        g_BattleEffectBattler->param.unk_0B = 0xFF;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F0548(void) {
    Effect_Reset();
}

MATCH void func_801F0568(void) {
    Magic008ThirdSteps handlers;

    handlers = D_801EEC70;
    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0) {
        Area_AddGridActor();
    }
}

/* The area scroll target as the one record retail reads it as: the Y read stays behind the X store. */
typedef struct {
    s32 x;
    s32 y;
} AreaScrollTarget;

/* Starts the effect: semi-transparent, tinted, at the scroll target on the battler's depth. */
MATCH void func_801F05FC(void) {
    PartyMember* work;
    s8           value;

    SELF(PartyMember)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    value                     = 1;
    SELF(PartyMember)->unk_5C = value;
    SELF(PartyMember)->unk_2B = value;
    value                     = -0x80;
    SELF(PartyMember)->unk_5D = value;
    SELF(PartyMember)->unk_5E = value;
    SELF(PartyMember)->unk_5F = value;
    work                      = g_Self;
    work->pos.x.fixed         = ((AreaScrollTarget*)&g_AreaScrollTargetX)->x;
    work->pos.y.fixed         = ((AreaScrollTarget*)&g_AreaScrollTargetX)->y;
    work->pos.z.fixed         = g_BattleEffectBattler->pos.z.fixed;
    work->unk_48              = 2;
    work->scale.x             = 0x18000;
    work->scale.y             = 0x28000;
    SELF(PartyMember)->unk_27 = g_BattleEffectBattler->unk_27;
    SND_SEQueueSelection(0x100);
    SELF(PartyMember)->unk_09 = 0x20;
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801F0710(void) {
    u8 count;

    SELF(PartyMember)->unk_5D += 3;
    SELF(PartyMember)->unk_5E += 3;
    SELF(PartyMember)->unk_5F += 3;
    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        SELF(PartyMember)->unk_09 = func_800AFF98();
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F07D4(void) {
    u8 counter;

    Script_AnimStepOnce();
    counter                   = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = counter;
    if (!(counter & BYTE_MASK)) {
        Battle_MarkDamaged(g_Battle.target_selector);
        Battle_PlayActiveBattlerSE(2, 4);
        SELF(PartyMember)->unk_09 = 0x20;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F0864(void) {
    if (Script_AnimStepOnce() & BYTE_MASK) {
        SND_SEQueueSelection(0x101);
        SELF(PartyMember)->unk_09 = 0x20;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F08C4(void) {
    u8 counter;

    SELF(PartyMember)->unk_5D -= 3;
    SELF(PartyMember)->unk_5E -= 3;
    SELF(PartyMember)->unk_5F -= 3;
    counter                   = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = counter;
    if (!(counter & BYTE_MASK)) {
        BATTLE_ACTIVE_WORK->param.unk_0B = 0xFF;
        Effect_Reset();
    }
}

/* func_801F0964 */
MATCH void BMagic_SkillStrikeEffectUpdate(void) {
    Magic008FirstSteps handlers;

    handlers = g_BMagicSkillStrikeSteps;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Self);
}

/* func_801F09D0 */
MATCH void BMagic_SkillStrikeEffectStart(void) {
    SELF(PartyMember)->unk_09      = func_800AFF98();
    SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;
    Area_AddGridActor();
}

/* func_801F0A20 */
MATCH void BMagic_SkillStrikeEffectSwing(void) {
    u8 timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        Script_AnimStepOnce();
        Battle_PlayActiveBattlerSE(2, 4);
        SELF(PartyMember)->header.step += 1;
    } else if (Script_AnimStepOnce() & BYTE_MASK) {
        Battle_PlayActiveBattlerSE(2, 4);
        SELF(PartyMember)->unk_09 = 0;
        SELF(PartyMember)->header.step += 1;
    }
    Area_AddGridActor();
}

/* func_801F0AC8 */
MATCH void BMagic_SkillStrikeEffectHit(void) {
    if (Script_AnimStepOnce() & BYTE_MASK) {
        Battle_MarkDamaged(g_Battle.target_selector);
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        SELF(PartyMember)->header.step += 1;
    }
    Area_AddGridActor();
}

/* func_801F0B44 */
MATCH void BMagic_SkillStrikeEffectEnd(void) {
    if (SELF(PartyMember)->unk_09 < 0xCU) {
        if (g_Battle.action_id != ABILITY_FEIGN_SWING) {
            Effect_DrawScreenFade();
        }
        SELF(PartyMember)->unk_09 += 4;
        return;
    }
    Effect_Reset();
}

#include "overlays/bmagic/shared/Effect_DrawScreenFade.h"

MATCH void func_801F0DA8(void) {
    BMagicEffectSteps handlers;

    handlers = D_801EEC94;
    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Area_AddGridActor();
    }
}

MATCH void func_801F0E54(void) {
    s8 tint;

    SELF(PartyMember)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    SELF(PartyMember)->unk_5C      = 1;
    SELF(PartyMember)->unk_2B      = 1;
    tint                           = -0x50;
    SELF(PartyMember)->unk_5D      = tint;
    SELF(PartyMember)->unk_5E      = tint;
    SELF(PartyMember)->unk_5F      = tint;
    SELF(PartyMember)->unk_27      = g_BattleEffectBattler->unk_27;
    SELF(PartyMember)->facing      = g_BattleEffectBattler->facing;
    SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    SELF(PartyMember)->unk_0C      = D_801F1C04[SELF(PartyMember)->param.unk_0B].x;
    SELF(PartyMember)->unk_10      = D_801F1C04[SELF(PartyMember)->param.unk_0B].y;
    Effect_RotatePosition(g_Self);
    SELF(PartyMember)->unk_09 = func_800AFF98();
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801F0FA4(void) {
    u8 value;

    if (g_FrameCount & 0x1) {
        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        Script_AnimStepOnce();
        value                     = SELF(PartyMember)->unk_09 - 1;
        SELF(PartyMember)->unk_09 = value;
        if (!(value & BYTE_MASK)) {
            SELF(PartyMember)->unk_09 = SELF(PartyMember)->param.unk_0B + 4;
            SELF(PartyMember)->header.step += 1;
        }
    } else {
        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + SELF(PartyMember)->unk_0C;
        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + SELF(PartyMember)->unk_10;
    }
}

MATCH void func_801F1090(void) {
    u8 value;

    if (g_FrameCount & 0x1) {
        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        value                          = SELF(PartyMember)->unk_09 - 1;
        SELF(PartyMember)->unk_09      = value;
        if (!(value & BYTE_MASK)) {
            if (SELF(PartyMember)->param.unk_0B == 0) {
                Battle_PlayActiveBattlerSE(2, 4);
                Battle_MarkDamaged(g_BattleTargetSelector);
            }
            SELF(PartyMember)->header.step += 1;
        }
    } else {
        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + SELF(PartyMember)->unk_0C;
        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + SELF(PartyMember)->unk_10;
    }
}

MATCH void func_801F117C(void) {
    if ((Script_AnimStepOnce() & BYTE_MASK) != 0u) {
        SELF(PartyMember)->header.step += 1u;
    }
}

MATCH void func_801F11C4(void) {
    SELF(PartyMember)->unk_5D -= 3;
    SELF(PartyMember)->unk_5E -= 3;
    SELF(PartyMember)->unk_5F -= 3;
    if ((s8)SELF(PartyMember)->unk_5D == -0x80) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F1274(void) {
    Effect_Reset();
}

MATCH void func_801F1294(void) {
    Magic008EarlySteps handlers;

    handlers = D_801EECAC;
    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0) {
        Area_AddGridActor();
    }
}

#include "overlays/bmagic/shared/Effect_SetDuration.h"

MATCH void func_801F1384(void) {
    u8 timer;

    MAGIC008_COUNT_DOWN_MARK_DAMAGED(2);
}

MATCH void func_801F1400(void) {
    if (Script_AnimStepOnce() & BYTE_MASK) {
        if (SELF(PartyMember)->header.step == 5) {
            g_BattleEffectBattler->param.unk_0B = 0xFF;
        }
        SELF(PartyMember)->header.step += 1;
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
    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0) {
        Area_AddGridActor();
    }
}

MATCH void Effect_ReloadTimerAndStep2(void) {
    BMAGIC_RELOAD_TIMER_AND_STEP();
}

MATCH void func_801F1804(void) {
    u8 timer;

    MAGIC008_COUNT_DOWN_MARK_DAMAGED(2);
}

MATCH void func_801F1880(void) {
    if (Script_AnimStepOnce() & BYTE_MASK) {
        if (SELF(PartyMember)->header.step == 8) {
            g_BattleEffectBattler->param.unk_0B = 0xFF;
        }
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F18F4(void) {
    /* FAKE: retail reserves 16 bytes of frame that no statement uses; pure C differs only in that frame. */
    FAKE_STACK_PADS(u8, 16);
    u8 count;

    MAGIC008_HIT_OR_ABORT(9);
    if (SELF(PartyMember)->header.step != 9 && g_Battle.action_id == 11 && (rand() & 7) == 0) {
        g_BattleEffectBattler->param.unk_0B = 0xFF;
        SELF(PartyMember)->header.step      = 9;
    }
}

MATCH void func_801F1BCC(void) {
    Effect_Reset();
}
