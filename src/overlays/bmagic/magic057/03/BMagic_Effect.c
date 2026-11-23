#include "magic057_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEC50 */
#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

MATCH void func_801EECB0(void) {
    TASK(PartyMember)->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed;
    TASK(PartyMember)->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed;
    TASK(PartyMember)->pos.z.fixed = BATTLE_ACTIVE_WORK->pos.z.fixed;
    GFX_PaletteCopy(26);
    g_GfxPalettePending += 1;
    TASK(PartyMember)->header.mode += 1;
}

MATCH void func_801EED2C(void) {
    Magic057Steps table;

    table = D_801EEC10;
    SYS_DISPATCH_TASK(table.steps, 2, g_Task);
}

MATCH void func_801EED98(void) {
    PartyMember* work;
    s32          slot;

    SND_SEQueueSelection(0x101);
    SND_SEQueueSelection(0x102);
    work   = TASK(PartyMember);
    g_Task = D_801EC2E0->target.party;
    Script_Select(3U);
    g_Task                             = work;
    slot                               = Battle_AllocEffect(1, 65) & BYTE_MASK;
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].header.step  = 0;
    g_BattleEffects[slot].target.party = TASK(PartyMember);
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EEE50(void) {
    PartyMember* work;

    work   = TASK(PartyMember);
    g_Task = D_801EC2E0->target.party;
    Script_AnimStepOnce();
    g_Task                   = work;
    work->unk_09             = 0;
    TASK(PartyMember)->timer = 0;
}

MATCH void func_801EEEB0(void) {
    PartyMember* battler;
    s32          z;
    u32          slot;

    if (g_FrameCount & 1) {
        if (TASK(PartyMember)->unk_09 < 0x20) {
            slot = Battle_AllocEffect(1, 0x41) & BYTE_MASK;
            if (slot != 0xFF) {
                g_BattleEffects[slot].header.mode  = 0;
                g_BattleEffects[slot].header.step  = 0;
                battler                            = g_BattleEffectBattler;
                g_BattleEffects[slot].pos.x.fixed  = battler->pos.x.fixed;
                g_BattleEffects[slot].pos.y.fixed  = battler->pos.y.fixed;
                z                                  = battler->pos.z.fixed;
                g_BattleEffects[slot].target.party = TASK(PartyMember);
                g_BattleEffects[slot].pos.z.fixed  = z;
                TASK(PartyMember)->unk_09 += 1;
            }
        } else {
            TASK(PartyMember)->header.step += 1;
        }
    }
}

MATCH void func_801EEFA4(void) {
    if (TASK(PartyMember)->unk_09 == TASK(PartyMember)->timer) {
        TASK(PartyMember)->header.mode += 1;
        TASK(PartyMember)->header.step = 0;
    }
}

MATCH void func_801EEFEC(void) {
    u16* battle_flags;

    battle_flags = &g_BattleState;
    *battle_flags |= 4;
    Battle_MarkDamaged(*(battle_flags = &g_Battle.target_selector));
    Effect_Reset();
}

MATCH void func_801EF02C(void) {
    Magic057SecondSteps handlers;

    handlers = D_801EEC20;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);
}

MATCH void func_801EF08C(void) {
    Magic057SecondSteps handlers;

    handlers  = D_801EEC2C;
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
    if (TASK(PartyMember)->header.flags & 0x1) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

#ifdef NON_MATCHING
NON_MATCHING void func_801EF134(void) {
    PartyMember* work;
    s32          dx;
    s32          dy;

    if (TASK(PartyMember)->facing & 1) {
        dx = (RANDOM_MOD(6) << 16) + 0x20000;
    } else {
        dx = (RANDOM_MOD(6) << 16) - 0x30000;
    }
    TASK(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + dx;
    if (TASK(PartyMember)->facing & 1) {
        dy = (RANDOM_MOD(6) << 16) + 0x30000;
    } else {
        dy = (RANDOM_MOD(6) << 16) + 0x20000;
    }
    TASK(PartyMember)->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed + dy;
    work                            = TASK(PartyMember);
    work->unk_14                    = -0x20;
    work->unk_20                    = -1;
    work->unk_25                    = 0x1D;
    work->pos.z.part.integer        = (u16)work->pos.z.part.integer + 0x600;
    TASK(PartyMember)->unk_26       = 0;
    TASK(PartyMember)->unk_48       = 1;
    TASK(PartyMember)->unk_27       = 0xA0;
    TASK(PartyMember)->unk_28       = 0;
    TASK(PartyMember)->unk_24       = 4;
    TASK(PartyMember)->unk_5D       = 0;
    TASK(PartyMember)->unk_5E       = 0;
    TASK(PartyMember)->unk_5F       = 0;
    TASK(PartyMember)->unk_5C       = 0;
    TASK(PartyMember)->unk_2A       = 0;
    TASK(PartyMember)->unk_29       = 4;
    TASK(PartyMember)->unk_2C.value = 0;
    Script_Select(0);
    TASK(PartyMember)->unk_09 = 3;
    TASK(PartyMember)->header.step += 1;
}
#else
INCLUDE_ASM(func_801EF134);
#endif

MATCH void func_801EF3C4(void) {
    s32 offset_x;
    s32 offset_y;
    u8  count;

    TASK(PartyMember)->pos.z.part.integer = (u16)TASK(PartyMember)->pos.z.part.integer + TASK(PartyMember)->unk_14;
    TASK(PartyMember)->unk_14             = TASK(PartyMember)->unk_14 + TASK(PartyMember)->unk_20;
    Script_AnimStepLoop();
    if (TASK(PartyMember)->pos.z.part.integer < Area_HeightSample(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed)) {
        offset_x                              = (RANDOM_MOD(6) << 16) + 0x20000;
        TASK(PartyMember)->pos.x.fixed        = g_BattleEffectBattler->pos.x.fixed + offset_x;
        offset_y                              = (RANDOM_MOD(6) << 16) - 0x30000;
        TASK(PartyMember)->pos.y.fixed        = g_BattleEffectBattler->pos.y.fixed + offset_y;
        TASK(PartyMember)->unk_14             = -0x20;
        TASK(PartyMember)->pos.z.part.integer = (u16)TASK(PartyMember)->pos.z.part.integer + 0x600;
        count                                 = TASK(PartyMember)->unk_09 - 1;
        TASK(PartyMember)->unk_09             = count;
        if (count == 0) {
            TASK(PartyMember)->header.step += 1;
        }
    }
}

MATCH void func_801EF528(void) {
    PartyMember* work;

    work        = (PartyMember*)g_BattleEffectBattler;
    work->timer = work->timer + 1;
    Effect_Reset();
}

MATCH void func_801EF55C(void) {
    Magic057SecondSteps handlers;

    handlers = D_801EEC38;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
}

MATCH void func_801EF5BC(void) {
    TASK(PartyMember)->unk_09 = 0;
    TASK(PartyMember)->timer  = D_801EFADC[TASK(PartyMember)->unk_09];
    SND_SEQueueSelection(256);
    TASK(PartyMember)->unk_10 = 0;
    TASK(PartyMember)->header.step++;
}

MATCH void func_801EF620(void) {
    Callback     handlers[2] = {func_801EF7A0, func_801EF7E0};
    PartyMember* phase_record;
    PartyMember* tail_record;
    PartyMember* work;
    u8           stage;
    s32          ramp;

    handlers[TASK(PartyMember)->unk_03]();
    if (TASK(PartyMember)->timer != 0xFF && --TASK(PartyMember)->timer == 0) {
        work         = TASK(PartyMember);
        stage        = work->unk_09 + 1;
        work->unk_09 = stage;
        work->timer  = D_801EFADC[stage];
        SND_SEQueueSelection(256);
        if (TASK(PartyMember)->unk_09 == 3) {
            g_BattleEffectBattler->header.step++;
            TASK(PartyMember)->timer = 0xFF;
        } else {
            TASK(PartyMember)->unk_03 = 0;
        }
    }
    if ((g_BattleEffectBattler->header.flags & 1) == 0) {
        tail_record = TASK(PartyMember);
        tail_record->header.step += 1;
        tail_record->unk_10  = 0;
        phase_record         = TASK(PartyMember);
        phase_record->unk_03 = 0;
    }
    ramp                     = TASK(PartyMember)->unk_10;
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetY      = ramp << 1;
}

MATCH void func_801EF7A0(void) {
    PartyMember* work;

    work = TASK(PartyMember);
    if (work->unk_10 >= -2) {
        work->unk_10--;
    } else {
        work->unk_03++;
    }
}

MATCH void func_801EF7E0(void) {
    PartyMember* work;

    work = TASK(PartyMember);
    if (work->unk_10 < 0) {
        work->unk_10++;
    } else {
        work->unk_03--;
    }
}

MATCH void func_801EF81C(void) {
    Effect_Reset();
}

MATCH void func_801EF83C(void) {
    Magic057SecondSteps handlers;

    handlers  = D_801EEC44;
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
    if ((TASK(PartyMember)->header.flags & 0x1) && (g_BattleEffectBattler->timer == 0)) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF900(void) {
    PartyMember* work;
    s16          height;
    s32          x;
    s8           tone;

    TASK(PartyMember)->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed - 1;
    TASK(PartyMember)->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed - 1;
    x                               = TASK(PartyMember)->pos.x.fixed;
    height                          = Area_HeightSample(x, x);
    work                            = TASK(PartyMember);
    work->unk_25                    = 0x1D;
    COORD_INT(work->pos.z)          = height;
    TASK(PartyMember)->unk_26       = 0;
    TASK(PartyMember)->unk_48       = 1;
    TASK(PartyMember)->unk_27       = 0xA0;
    TASK(PartyMember)->unk_28       = 0;
    TASK(PartyMember)->unk_24       = 4;
    tone                            = -0x80;
    TASK(PartyMember)->unk_5D       = tone;
    TASK(PartyMember)->unk_5E       = tone;
    TASK(PartyMember)->unk_5F       = tone;
    TASK(PartyMember)->unk_5C       = 0;
    TASK(PartyMember)->unk_2A       = 0;
    TASK(PartyMember)->unk_29       = 4;
    TASK(PartyMember)->unk_2C.value = 0;
    Script_Select(0U);
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EFA38(void) {
    s32 x;

    TASK(PartyMember)->pos.x.fixed      = g_BattleEffectBattler->pos.x.fixed - 1;
    TASK(PartyMember)->pos.y.fixed      = g_BattleEffectBattler->pos.y.fixed - 1;
    x                                   = TASK(PartyMember)->pos.x.fixed;
    COORD_INT(TASK(PartyMember)->pos.z) = Area_HeightSample(x, x);
    if (!(0x1 & g_BattleEffectBattler->header.flags)) {
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EFABC(void) {
    Effect_Reset();
}
