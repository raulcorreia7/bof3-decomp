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
    func_800AEF98(0xC, 2);
    BMAGIC_QUEUE_WORK_IMAGE();
    work                                             = g_Task;
    g_BattleEffects[index & BYTE_MASK].unk_06        = 1;
    g_BattleEffects[index & BYTE_MASK].header.mode   = 0;
    g_BattleEffects[index & BYTE_MASK].header.step   = 0;
    g_BattleEffects[index & BYTE_MASK].handler_index = 31;
    g_BattleEffects[index & BYTE_MASK].target.party  = work;
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
    SND_QueueSelectionFx(0x100);
}

MATCH void func_801EEF6C(void) {
    if (g_Task->param.unk_0B == 0xFF) {
        func_800AEF98(4, 0);
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

INCLUDE_ASM(func_801EF0B8);

MATCH void func_801EF324(void) {
    u16* battle_flags;

    if (g_Task->param.unk_0B == 0xFF) {
        func_800AFC54();
        func_800AEF98(4, 0);
        battle_flags = &g_Battle.state;
        *battle_flags |= 4;
        func_801E5988();
    }
}

MATCH void func_801EF384(void) {
    Magic008FirstSteps handlers;

    handlers = D_801EEC20;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);
}

INCLUDE_ASM(func_801EF3F0);

#include "overlays/bmagic/Effect_RestorePaletteAndReleaseActive.h"

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
    func_800AEF98(0xC, 2);
    BMAGIC_QUEUE_WORK_IMAGE();
    work                                             = g_Task;
    g_BattleEffects[index & BYTE_MASK].header.mode   = 4;
    g_BattleEffects[index & BYTE_MASK].unk_06        = 1;
    g_BattleEffects[index & BYTE_MASK].header.step   = 0;
    g_BattleEffects[index & BYTE_MASK].handler_index = 31;
    g_BattleEffects[index & BYTE_MASK].target.party  = work;
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
}

MATCH void func_801EF9D4(void) {
    if (g_Task->param.unk_0B == 0xFF) {
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        func_800AEF98(4, 0);
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

MATCH void func_801EFAD4(void) {
    BattleEffect* slot;
    PartyMember*  work;
    u32           index;
    u8            active;

    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    func_800AEF98(0xC, 2);
    BMAGIC_QUEUE_WORK_IMAGE();
    work                                             = g_Task;
    g_BattleEffects[index & BYTE_MASK].header.mode   = 5;
    g_BattleEffects[index & BYTE_MASK].unk_06        = 1;
    g_BattleEffects[index & BYTE_MASK].header.step   = 0;
    g_BattleEffects[index & BYTE_MASK].handler_index = 31;
    g_BattleEffects[index & BYTE_MASK].target.party  = work;
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
}

MATCH void func_801EFC90(void) {
    if (g_Task->param.unk_0B == 0xFF) {
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        func_800AEF98(4, 0);
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

INCLUDE_ASM(func_801EFD90);

INCLUDE_ASM(func_801F0018);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH u32 func_801F0230(void) {
    return LOHU(g_Battle.action_id) == 7 ? 7 : 0xFF;
}

/* func_801F0250 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801F0294(void) {
    BMagicEffectFuncs handlers;

    handlers = D_801EEC58;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_8014D290();
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
        func_800AFC98(2, 4);
        g_Task->header.step += 1;
    }
}

MATCH void func_801F047C(void) {
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        SND_QueueSelectionFx(0x101);
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
    func_801E5988();
}

MATCH void func_801F0568(void) {
    Magic008ThirdSteps handlers;

    handlers = D_801EEC70;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_8014D290();
    }
}

INCLUDE_ASM(func_801F05FC);

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
        func_800AFC98(2, 4);
        g_Task->unk_09 = 0x20;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0864(void) {
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        SND_QueueSelectionFx(0x101);
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
        func_801E5988();
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
    func_8014D290();
}

MATCH void func_801F0A20(void) {
    u8 value;

    value          = g_Task->unk_09 - 1;
    g_Task->unk_09 = value;
    if (!(value & BYTE_MASK)) {
        Actor_StepAnimOnce();
        func_800AFC98(2, 4);
        g_Task->header.step += 1;
    } else if (Actor_StepAnimOnce() & BYTE_MASK) {
        func_800AFC98(2, 4);
        g_Task->unk_09 = 0;
        g_Task->header.step += 1;
    }
    func_8014D290();
}

MATCH void func_801F0AC8(void) {
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        Battle_MarkDamaged(g_Battle.target_selector);
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        g_Task->header.step += 1;
    }
    func_8014D290();
}

MATCH void func_801F0B44(void) {
    u16* battle_half;

    if (g_Task->unk_09 < 0xCU) {
        battle_half = (u16*)&g_Battle.action_id;
        if (*battle_half != 0xA4) {
            Effect_DrawScreenFade();
        }
        g_Task->unk_09 += 4;
        return;
    }
    func_801E5988();
}

#include "overlays/bmagic/Effect_DrawScreenFade.h"

MATCH void func_801F0DA8(void) {
    BMagicEffectFuncs handlers;

    handlers = D_801EEC94;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
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
    func_801DD350(g_Task);
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
                func_800AFC98(2, 4);
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
    func_801E5988();
}

MATCH void func_801F1294(void) {
    Magic008EarlySteps handlers;

    handlers = D_801EECAC;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_8014D290();
    }
}

#include "overlays/bmagic/Effect_SetDuration.h"

MATCH void func_801F1384(void) {
    u8 timer;

    Actor_StepAnimOnce();
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        func_800AFC98(2, 0);
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

INCLUDE_ASM(func_801F1474);

MATCH void func_801F16E8(void) {
    func_801E5988();
}

MATCH void func_801F1708(void) {
    Magic008Steps handlers;

    handlers = D_801EECC8;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_8014D290();
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
        func_800AFC98(2, 0);
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

INCLUDE_ASM(func_801F18F4);

MATCH void func_801F1BCC(void) {
    func_801E5988();
}
