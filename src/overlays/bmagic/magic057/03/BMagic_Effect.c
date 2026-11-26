#include "magic057_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEC50 */
#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

/* Places the task at the active battler, copies palette 26 and advances the task mode. */
/* func_801EECB0 */
MATCH void BMagic_BoneDanceInit(void) {
    SELF(PartyMember)->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed;
    SELF(PartyMember)->pos.z.fixed = BATTLE_ACTIVE_WORK->pos.z.fixed;
    GFX_PaletteCopy(26);
    g_GfxPalettePending += 1;
    SELF(PartyMember)->header.mode += 1;
}

/* Runs the task step that header.step (byte 0x02) selects from g_BMagicBoneDanceTaskSteps. */
/* func_801EED2C */
MATCH void BMagic_BoneDanceTaskUpdate(void) {
    Magic057Steps table;

    table = g_BMagicBoneDanceTaskSteps;
    SYS_DISPATCH_TASK(table.steps, 2, g_Self);
}

/* Task step 0: queues the two sounds, selects script 3 for the actor of the effect the task runs on and spawns the shake effect. */
/* func_801EED98 */
MATCH void BMagic_BoneDanceStart(void) {
    PartyMember* work;
    s32          slot;

    SND_SEQueueSelection(0x101);
    SND_SEQueueSelection(0x102);
    work   = SELF(PartyMember);
    g_Self = D_801EC2E0->target.party;
    Script_Select(3U);
    g_Self                             = work;
    slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_BONE_DANCE) & BYTE_MASK;
    g_BattleEffects[slot].header.mode  = BMAGIC_BONE_DANCE_EFFECT_SHAKE;
    g_BattleEffects[slot].header.step  = 0;
    g_BattleEffects[slot].target.party = SELF(PartyMember);
    SELF(PartyMember)->header.step += 1;
}

/* Task step 1: plays the actor's script and zeroes the bone counts each frame until the shake effect advances the step. */
/* func_801EEE50 */
MATCH void BMagic_BoneDanceWaitShake(void) {
    PartyMember* work;

    work   = SELF(PartyMember);
    g_Self = D_801EC2E0->target.party;
    Script_AnimStepOnce();
    g_Self                   = work;
    work->unk_09             = 0;
    SELF(PartyMember)->timer = 0;
}

/* Task step 2: on odd frames spawns a bone effect at the effect battler, up to 32, then advances the step. */
/* func_801EEEB0 */
MATCH void BMagic_BoneDanceSpawnBones(void) {
    PartyMember* battler;
    s32          z;
    u32          slot;

    if (g_FrameCount & 1) {
        if (SELF(PartyMember)->unk_09 < BMAGIC_BONE_DANCE_BONE_COUNT) {
            slot = Battle_AllocEffect(1, BMAGIC_EFFECT_BONE_DANCE) & BYTE_MASK;
            if (slot != 0xFF) {
                g_BattleEffects[slot].header.mode  = BMAGIC_BONE_DANCE_EFFECT_BONE;
                g_BattleEffects[slot].header.step  = 0;
                battler                            = g_BattleEffectBattler;
                g_BattleEffects[slot].pos.x.fixed  = battler->pos.x.fixed;
                g_BattleEffects[slot].pos.y.fixed  = battler->pos.y.fixed;
                z                                  = battler->pos.z.fixed;
                g_BattleEffects[slot].target.party = SELF(PartyMember);
                g_BattleEffects[slot].pos.z.fixed  = z;
                SELF(PartyMember)->unk_09 += 1;
            }
        } else {
            SELF(PartyMember)->header.step += 1;
        }
    }
}

/* Task step 3: once every bone has ended (the ended count in byte 0x0A equals the spawned count in byte 0x09), advances the task mode. */
/* func_801EEFA4 */
MATCH void BMagic_BoneDanceWaitBones(void) {
    if (SELF(PartyMember)->unk_09 == SELF(PartyMember)->timer) {
        SELF(PartyMember)->header.mode += 1;
        SELF(PartyMember)->header.step = 0;
    }
}

/* Raises BATTLE_STATE_EFFECT_PLAYING, marks the selected battlers damaged and clears the effect. */
/* func_801EEFEC */
MATCH void BMagic_BoneDanceEnd(void) {
    u16* battle_flags;

    battle_flags = &g_BattleState;
    *battle_flags |= 4;
    Battle_MarkDamaged(*(battle_flags = &g_Battle.target_selector));
    Effect_Reset();
}

/* Runs the effect routine that header.mode (byte 0x01) selects from g_BMagicBoneDanceEffectModes. */
/* func_801EF02C */
MATCH void BMagic_BoneDanceEffectUpdate(void) {
    Magic057SecondSteps handlers;

    handlers = g_BMagicBoneDanceEffectModes;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Self);
}

/* Runs the bone step that header.step selects with the battle script table set, and draws the bone while its effect is in use. */
/* func_801EF08C */
MATCH void BMagic_BoneDanceBoneUpdate(void) {
    Magic057SecondSteps handlers;

    handlers  = g_BMagicBoneDanceBoneSteps;
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Self);
    if (SELF(PartyMember)->header.flags & 0x1) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

/* Places the effect at a random offset on the battler's facing side, lifts it by 0x600 and starts its arc. */
/* func_801EF134 */
MATCH void BMagic_BoneDanceBoneStart(void) {
    PartyMember* work;

    if (SELF(PartyMember)->facing & 1) {
        s32 offset = (RANDOM_MOD(6) << 16) + 0x20000;

        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + offset;
    } else {
        s32 offset = (RANDOM_MOD(6) << 16) - 0x30000;

        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + offset;
    }
    if (SELF(PartyMember)->facing & 1) {
        s32 offset = (RANDOM_MOD(6) << 16) + 0x30000;

        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + offset;
    } else {
        s32 offset = (RANDOM_MOD(6) << 16) + 0x20000;

        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + offset;
    }
    work                            = SELF(PartyMember);
    work->unk_14                    = -0x20;
    work->unk_20                    = -1;
    work->unk_25                    = 0x1D;
    work->pos.z.part.integer        = (u16)work->pos.z.part.integer + 0x600;
    SELF(PartyMember)->unk_26       = 0;
    SELF(PartyMember)->unk_48       = 1;
    SELF(PartyMember)->unk_27       = 0xA0;
    SELF(PartyMember)->unk_28       = 0;
    SELF(PartyMember)->unk_24       = 4;
    SELF(PartyMember)->unk_5D       = 0;
    SELF(PartyMember)->unk_5E       = 0;
    SELF(PartyMember)->unk_5F       = 0;
    SELF(PartyMember)->unk_5C       = 0;
    SELF(PartyMember)->unk_2A       = 0;
    SELF(PartyMember)->unk_29       = 4;
    SELF(PartyMember)->unk_2C.value = 0;
    Script_Select(0);
    SELF(PartyMember)->unk_09 = BMAGIC_BONE_DANCE_BONE_BOUNCES;
    SELF(PartyMember)->header.step += 1;
}

/* Bone step 1: moves the bone along its arc; each time it reaches the ground it jumps to a new random offset, and after 3 bounces it advances the step. */
/* func_801EF3C4 */
MATCH void BMagic_BoneDanceBoneBounce(void) {
    s32 offset_x;
    s32 offset_y;
    u8  count;

    SELF(PartyMember)->pos.z.part.integer = (u16)SELF(PartyMember)->pos.z.part.integer + SELF(PartyMember)->unk_14;
    SELF(PartyMember)->unk_14             = SELF(PartyMember)->unk_14 + SELF(PartyMember)->unk_20;
    Script_AnimStepLoop();
    if (SELF(PartyMember)->pos.z.part.integer < Area_HeightSample(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed)) {
        offset_x                              = (RANDOM_MOD(6) << 16) + 0x20000;
        SELF(PartyMember)->pos.x.fixed        = g_BattleEffectBattler->pos.x.fixed + offset_x;
        offset_y                              = (RANDOM_MOD(6) << 16) - 0x30000;
        SELF(PartyMember)->pos.y.fixed        = g_BattleEffectBattler->pos.y.fixed + offset_y;
        SELF(PartyMember)->unk_14             = -0x20;
        SELF(PartyMember)->pos.z.part.integer = (u16)SELF(PartyMember)->pos.z.part.integer + 0x600;
        count                                 = SELF(PartyMember)->unk_09 - 1;
        SELF(PartyMember)->unk_09             = count;
        if (count == 0) {
            SELF(PartyMember)->header.step += 1;
        }
    }
}

/* Bone step 2: counts the bone as ended on the task (byte 0x0A) and clears the effect. */
/* func_801EF528 */
MATCH void BMagic_BoneDanceBoneEnd(void) {
    PartyMember* work;

    work        = (PartyMember*)g_BattleEffectBattler;
    work->timer = work->timer + 1;
    Effect_Reset();
}

/* Runs the shake step that header.step selects from g_BMagicBoneDanceShakeSteps. */
/* func_801EF55C */
MATCH void BMagic_BoneDanceShakeUpdate(void) {
    Magic057SecondSteps handlers;

    handlers = g_BMagicBoneDanceShakeSteps;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Self);
}

/* Shake step 0: loads the length of the first shake and queues its sound. */
/* func_801EF5BC */
MATCH void BMagic_BoneDanceShakeStart(void) {
    SELF(PartyMember)->unk_09 = 0;
    SELF(PartyMember)->timer  = g_BMagicBoneDanceShakeFrames[SELF(PartyMember)->unk_09];
    SND_SEQueueSelection(256);
    SELF(PartyMember)->unk_10 = 0;
    SELF(PartyMember)->header.step++;
}

/* Shake step 1: runs the shake phase, moves the camera by its offset, and at the end of each of 3 shakes queues the sound again; after the third it advances the task. */
/* func_801EF620 */
MATCH void BMagic_BoneDanceShakeRun(void) {
    Callback     handlers[2] = {BMagic_BoneDanceShakeDown, BMagic_BoneDanceShakeUp};
    PartyMember* phase_record;
    PartyMember* tail_record;
    PartyMember* work;
    u8           stage;
    s32          ramp;

    handlers[SELF(PartyMember)->unk_03]();
    if (SELF(PartyMember)->timer != 0xFF && --SELF(PartyMember)->timer == 0) {
        work         = SELF(PartyMember);
        stage        = work->unk_09 + 1;
        work->unk_09 = stage;
        work->timer  = g_BMagicBoneDanceShakeFrames[stage];
        SND_SEQueueSelection(256);
        if (SELF(PartyMember)->unk_09 == BMAGIC_BONE_DANCE_SHAKE_COUNT) {
            g_BattleEffectBattler->header.step++;
            SELF(PartyMember)->timer = 0xFF;
        } else {
            SELF(PartyMember)->unk_03 = 0;
        }
    }
    if ((g_BattleEffectBattler->header.flags & 1) == 0) {
        tail_record = SELF(PartyMember);
        tail_record->header.step += 1;
        tail_record->unk_10  = 0;
        phase_record         = SELF(PartyMember);
        phase_record->unk_03 = 0;
    }
    ramp                     = SELF(PartyMember)->unk_10;
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetY      = ramp << 1;
}

/* Shake phase 0: lowers the camera offset to -3, then switches to the rise phase. */
/* func_801EF7A0 */
MATCH void BMagic_BoneDanceShakeDown(void) {
    PartyMember* work;

    work = SELF(PartyMember);
    if (work->unk_10 >= -2) {
        work->unk_10--;
    } else {
        work->unk_03++;
    }
}

/* Shake phase 1: raises the camera offset back to 0, then switches to the drop phase. */
/* func_801EF7E0 */
MATCH void BMagic_BoneDanceShakeUp(void) {
    PartyMember* work;

    work = SELF(PartyMember);
    if (work->unk_10 < 0) {
        work->unk_10++;
    } else {
        work->unk_03--;
    }
}

/* Shake step 2: clears the effect. */
/* func_801EF81C */
MATCH void BMagic_BoneDanceShakeEnd(void) {
    Effect_Reset();
}

/* Runs the ground step that header.step selects with the battle script table set, and draws it until the first bone has ended (the task's byte 0x0A is 0). */
/* func_801EF83C */
MATCH void BMagic_BoneDanceGroundUpdate(void) {
    Magic057SecondSteps handlers;

    handlers  = g_BMagicBoneDanceGroundSteps;
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Self);
    if ((SELF(PartyMember)->header.flags & 0x1) && (g_BattleEffectBattler->timer == 0)) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

/* Ground step 0: places the actor on the ground height at the effect battler and starts script 0 dark. */
/* func_801EF900 */
MATCH void BMagic_BoneDanceGroundStart(void) {
    PartyMember* work;
    s16          height;
    s32          x;
    s8           tone;

    SELF(PartyMember)->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed - 1;
    SELF(PartyMember)->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed - 1;
    x                               = SELF(PartyMember)->pos.x.fixed;
    height                          = Area_HeightSample(x, x);
    work                            = SELF(PartyMember);
    work->unk_25                    = 0x1D;
    COORD_INT(work->pos.z)          = height;
    SELF(PartyMember)->unk_26       = 0;
    SELF(PartyMember)->unk_48       = 1;
    SELF(PartyMember)->unk_27       = 0xA0;
    SELF(PartyMember)->unk_28       = 0;
    SELF(PartyMember)->unk_24       = 4;
    tone                            = -0x80;
    SELF(PartyMember)->unk_5D       = tone;
    SELF(PartyMember)->unk_5E       = tone;
    SELF(PartyMember)->unk_5F       = tone;
    SELF(PartyMember)->unk_5C       = 0;
    SELF(PartyMember)->unk_2A       = 0;
    SELF(PartyMember)->unk_29       = 4;
    SELF(PartyMember)->unk_2C.value = 0;
    Script_Select(0U);
    SELF(PartyMember)->header.step += 1;
}

/* Ground step 1: keeps the actor on the ground height at the effect battler until that effect ends. */
/* func_801EFA38 */
MATCH void BMagic_BoneDanceGroundFollow(void) {
    s32 x;

    SELF(PartyMember)->pos.x.fixed      = g_BattleEffectBattler->pos.x.fixed - 1;
    SELF(PartyMember)->pos.y.fixed      = g_BattleEffectBattler->pos.y.fixed - 1;
    x                                   = SELF(PartyMember)->pos.x.fixed;
    COORD_INT(SELF(PartyMember)->pos.z) = Area_HeightSample(x, x);
    if (!(0x1 & g_BattleEffectBattler->header.flags)) {
        SELF(PartyMember)->header.step += 1;
    }
}

/* Ground step 2: clears the effect. */
/* func_801EFABC */
MATCH void BMagic_BoneDanceGroundEnd(void) {
    Effect_Reset();
}
