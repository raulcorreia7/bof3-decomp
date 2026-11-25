#include "magic131_03.h"
#include "sys/scratchpad.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEC24 */
MATCH void BMagic_KaiserBreathUpdate(void) {
    Callback     handlers[8];
    PartyMember* saved_battler;
    s32          tpage;
    u8           i;

    __builtin_memcpy(handlers, g_BMagicKaiserBreathModes, sizeof(handlers));
    SYS_DISPATCH_BYTE(handlers, TASK(PartyMember)->header.mode);
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
    for (i = 0; i < ARRAY_COUNT(g_BMagicKaiserBreathParticles); i++) {
        if (g_BMagicKaiserBreathParticles[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_battler                = g_BattleEffectBattler;
            g_BMagicKaiserBreathParticle = &g_BMagicKaiserBreathParticles[i];
            g_BattleEffectBattler        = g_BMagicKaiserBreathParticles[i].battler;
            BMagic_KaiserBreathRunParticle();
            g_BattleEffectBattler = saved_battler;
        }
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
}

/* func_801EEDEC */
MATCH void BMagic_KaiserBreathInit(void) {
    PartyMember* target;
    u16*         src;
    u16*         dst;
    u16          i;
    u32          slot;

    for (i = 0; i < ARRAY_COUNT(g_BMagicKaiserBreathParticles); i++) {
        g_BMagicKaiserBreathParticles[i].header.flags = 0;
        g_BMagicKaiserBreathParticles[i].header.mode  = 0;
        g_BMagicKaiserBreathParticles[i].header.step  = 0;
    }
    TASK(PartyMember)->facing = g_BattleEffectBattler->facing;
    Battle_CenterCamera();
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 10;
    TASK(PartyMember)->timer        = 0;
    TASK(PartyMember)->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 105) & BYTE_MASK;
    target                             = TASK(PartyMember);
    g_BattleEffects[slot].header.mode  = KAISER_BREATH_EFFECT_FLASH;
    g_BattleEffects[slot].target.party = target;
    TASK(PartyMember)->param.unk_0B += 1;
    BMAGIC_BRIGHTEN_PALETTE_ROW(dst, src, i);
    g_GfxPalettePending = 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x02));
}

/* Loads the archive of the current dragon form once the step timer runs out. */
/* func_801EEF64 */
MATCH void BMagic_KaiserBreathLoadDragon(void) {
    u32 archive;
    u8  timer;

    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        switch (g_Battle.dragon_form) {
            case DRAGON_FORM_WILDFIRE:
            default:
                archive = EMI_SLOT_KAIZAR_N;
                break;
            case DRAGON_FORM_FAILURE_KAISER:
                archive = EMI_SLOT_KAIZAR_F;
                break;
            case DRAGON_FORM_BERSERK_KAISER:
                archive = EMI_SLOT_KAIZAR_D;
                break;
        }
        EMI_ArchiveLoad(archive);
        TASK(PartyMember)->header.mode += 1;
    }
}

/* func_801EF000 */
MATCH void BMagic_KaiserBreathStartDragon(void) {
    u16          i;
    u32          slot;
    PartyMember* work;

    if (!EMI_IsReady()) {
        return;
    }
    g_Game.members[0].header.flags     = 0;
    g_Game.members[1].header.flags     = 0;
    g_Game.members[2].header.flags     = 0;
    slot                               = Battle_AllocEffect(1, 0x69) & BYTE_MASK;
    work                               = TASK(PartyMember);
    g_BattleEffects[slot].unk_04       = 0x21;
    g_BattleEffects[slot].header.mode  = KAISER_BREATH_EFFECT_DRAGON;
    g_BattleEffects[slot].arg.unk_09   = 0x18;
    g_BattleEffects[slot].target.party = work;
    TASK(PartyMember)->param.unk_0B += 1;
    for (i = 0; i < AREA_PALETTE_COLORS; i++) {
        MEM(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BMAGIC_ROW) + i * 2) = MEM(u16, AREA_PALETTE_ARENA_33C00 + i * 2);
    }
    g_GfxPalettePending = 1;
    TASK(PartyMember)->header.mode += 1;
}

/* func_801EF110 */
MATCH void BMagic_KaiserBreathWaitDragon(void) {
    PartyMember* work;
    u32          slot;

    if (TASK(PartyMember)->param.unk_0B == 0) {
        slot                               = Battle_AllocEffect(1, 0x69) & BYTE_MASK;
        work                               = TASK(PartyMember);
        g_BattleEffects[slot].header.mode  = KAISER_BREATH_EFFECT_FLASH;
        g_BattleEffects[slot].target.party = work;
        TASK(PartyMember)->param.unk_0B++;
        TASK(PartyMember)->unk_09 = 10;
        TASK(PartyMember)->header.mode++;
    }
}

/* func_801EF1C0 */
MATCH void BMagic_KaiserBreathLoadCharacter(void) {
    u8 count;
    u8 found;
    u8 i;

    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    found                     = 0;
    if (count != 0) {
        return;
    }
    for (i = 0; i < g_Game.party_size; i++) {
        if (g_Game.members[i].chr.character_id == CHAR_ID_REI && (g_Game.members[i].u.turn.action_flags.value & BATTLER_ACTION_DRAGON_FORM_QUEUED)) {
            found = 1;
        }
    }
    if (found) {
        if (g_EmiLoadedCharacterIndex == 7) {
            EMI_ArchiveLoad((g_Battle.scroll_dir & 0x2) ? EMI_SLOT_BRTU247 : EMI_SLOT_BRTD247);
        }
        if (g_EmiLoadedCharacterIndex == 0xD) {
            EMI_ArchiveLoad((g_Battle.scroll_dir & 0x2) ? EMI_SLOT_BRTU457 : EMI_SLOT_BRTD457);
        }
        if (g_EmiLoadedCharacterIndex == 0xE) {
            EMI_ArchiveLoad((g_Battle.scroll_dir & 0x2) ? EMI_SLOT_BRTU467 : EMI_SLOT_BRTD467);
        }
        if (g_EmiLoadedCharacterIndex == 0xF) {
            if (g_Battle.scroll_dir & 0x2) {
                EMI_ArchiveLoad(EMI_SLOT_BRTU478);
            } else {
                EMI_ArchiveLoad(EMI_SLOT_BRTD478);
            }
        }
    } else {
        if (g_Battle.scroll_dir & 0x2) {
            EMI_ArchiveLoadFamily(g_EmiLoadedCharacterIndex & 0x7F, 2);
        } else {
            EMI_ArchiveLoadFamily(g_EmiLoadedCharacterIndex & 0x7F, 1);
        }
    }
    TASK(PartyMember)->header.mode += 1;
}

/* func_801EF3D0 */
MATCH void BMagic_KaiserBreathLoadCharacterForm(void) {
    if (!EMI_IsReady()) {
        return;
    }
    if (g_Battle.scroll_dir & 0x2) {
        EMI_ArchiveLoad(D_800B499C[g_Battle.dragon_form][1][g_EmiLoadedCharacterIndex]);
    } else {
        EMI_ArchiveLoad(D_800B499C[g_Battle.dragon_form][0][g_EmiLoadedCharacterIndex]);
    }
    TASK(PartyMember)->header.mode += 1;
}

/* func_801EF488 */
MATCH void BMagic_KaiserBreathShowParty(void) {
    PartyMember* prev;
    PartyMember* battler;
    s32          i;
    s32          slot;

    if (EMI_IsReady() != 0) {
        i = 0;
        if (g_Game.party_size != 0) {
            do {
                slot                              = i & BYTE_MASK;
                g_Game.members[slot].header.flags = ACTOR_FLAG_IN_USE;
                prev                              = TASK(PartyMember);
                battler                           = &g_Game.members[slot];
                g_Task                            = battler;
                Script_Select((battler->facing + 4) & BYTE_MASK);
                if (g_Game.members[slot].chr.status & (STATUS_LOW_HP | STATUS_POISONED)) {
                    Script_Select((TASK(PartyMember)->facing + 0x18) & BYTE_MASK);
                }
                if (g_Game.members[slot].chr.status & STATUS_UNK_11) {
                    Script_Select((TASK(PartyMember)->facing + 0x30) & BYTE_MASK);
                }
                if (Battle_SlotIsBlocked(slot) & BYTE_MASK) {
                    Script_Select((TASK(PartyMember)->facing + 0x1C) & BYTE_MASK);
                }
                i++;
                g_Task = prev;
            } while ((u32)(i & BYTE_MASK) < g_PartySize);
        }
        TASK(PartyMember)->header.mode++;
    }
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

/* func_801EF668 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

/* Runs the effect step with g_Scripts on the character sprites, then cycles nine colours of the
 * battle magic palette row every fourth frame. */
/* func_801EF6AC */
MATCH void BMagic_KaiserBreathRunDragon(void) {
    u16* dst;
    u16* src;
    u8   i;

    g_Scripts = CHARACTER_SPRITES_BASE;
    SYS_DISPATCH_BYTE(g_BMagicKaiserBreathDragonSteps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Area_AddGridActor();
        if ((g_FrameCount & 3) == 0) {
            i   = 0;
            dst = g_AreaPaletteCopy->rows[AREA_PALETTE_BMAGIC_ROW].colors;
            src = g_AreaPaletteArena->rows[AREA_PALETTE_BMAGIC_ROW].colors;
            for (; i < 9; i++) {
                dst[i + 0x21] = src[TASK(PartyMember)->unk_04 + i] | PSX_COLOR_STP_BIT;
            }
            g_GfxPalettePending = 1;
            TASK(PartyMember)->unk_04 += 9;
            if (TASK(PartyMember)->unk_04 >= 0x7B) {
                TASK(PartyMember)->unk_04 = 0x21;
            }
        }
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

/* func_801EF7FC */
MATCH void BMagic_KaiserBreathDragonStart(void) {
    PartyMember* work;
    PartyMember* task;
    PartyMember* actor;
    u8           count;
    u8           i;

    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (count != 0) {
        return;
    }
    if (g_Battle.scroll_dir == 0 || g_Battle.scroll_dir == 3) {
        TASK(PartyMember)->screen_x.value = 0x3D;
        TASK(PartyMember)->screen_y.value = 0x46;
        TASK(PartyMember)->unk_0C         = -4;
        TASK(PartyMember)->unk_10         = -4;
        TASK(PartyMember)->unk_18         = -1;
        TASK(PartyMember)->unk_1C         = -1;
        TASK(PartyMember)->unk_2A         = 1;
    } else {
        TASK(PartyMember)->screen_x.value = 0x103;
        TASK(PartyMember)->screen_y.value = 0x46;
        TASK(PartyMember)->unk_0C         = 4;
        TASK(PartyMember)->unk_10         = -4;
        TASK(PartyMember)->unk_18         = 1;
        TASK(PartyMember)->unk_1C         = -1;
        TASK(PartyMember)->unk_2A         = 0;
    }
    work = TASK(PartyMember);
    for (i = 0; i < 16; i++) {
        work->unk_0C += work->unk_18;
        work->unk_10 += work->unk_1C;
        work->screen_x.value += work->unk_0C;
        work->screen_y.value += work->unk_10;
    }
    task                      = TASK(PartyMember);
    task->unk_0C              = ~task->unk_0C + 1;
    task->unk_25              = 5;
    task->unk_10              = ~task->unk_10 + 1;
    TASK(PartyMember)->unk_26 = 0;
    TASK(PartyMember)->unk_27 = 2;
    TASK(PartyMember)->unk_28 = 1;
    TASK(PartyMember)->unk_24 = 0x80;
    actor                     = TASK(PartyMember);
    actor->unk_48             = 0;
    actor->scale.x            = 0x10000;
    actor->scale.y            = 0x10000;
    TASK(PartyMember)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    TASK(PartyMember)->unk_5C       = 0;
    TASK(PartyMember)->unk_5D       = 0;
    TASK(PartyMember)->unk_5E       = 0;
    TASK(PartyMember)->unk_5F       = 0;
    TASK(PartyMember)->unk_29       = 2;
    TASK(PartyMember)->unk_2C.value = 0;
    TASK(PartyMember)->unk_2B       = 0;
    Script_Select(0);
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x01));
    TASK(PartyMember)->unk_09 = 0x10;
    TASK(PartyMember)->header.step += 1;
}

/* func_801EFA68 */
MATCH void BMagic_KaiserBreathDragonFlyIn(void) {
    u8 count;

    TASK(PartyMember)->screen_x.value += TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->screen_y.value += TASK(PartyMember)->unk_10;
    TASK(PartyMember)->unk_0C += TASK(PartyMember)->unk_18;
    TASK(PartyMember)->unk_10 += TASK(PartyMember)->unk_1C;
    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (count & BYTE_MASK) {
        return;
    }
    if (g_Battle.scroll_dir == 0 || g_Battle.scroll_dir == 3) {
        TASK(PartyMember)->unk_0C = 4;
        TASK(PartyMember)->unk_10 = 4;
        TASK(PartyMember)->unk_18 = -1;
        TASK(PartyMember)->unk_1C = -1;
    } else {
        TASK(PartyMember)->unk_0C = -4;
        TASK(PartyMember)->unk_10 = 4;
        TASK(PartyMember)->unk_18 = 1;
        TASK(PartyMember)->unk_1C = -1;
    }
    TASK(PartyMember)->unk_09 = 6;
    TASK(PartyMember)->header.step++;
}

/* func_801EFB64 */
MATCH void BMagic_KaiserBreathDragonSettle(void) {
    PartyMember* work  = TASK(PartyMember);
    u8           timer = work->unk_09 - 1;
    work->unk_0C += work->unk_18;
    work->unk_09 = timer;
    work->unk_10 += work->unk_1C;
    work->screen_x.value += work->unk_0C;
    work->screen_y.value += work->unk_10;
    if (timer == 0) {
        TASK(PartyMember)->unk_09 = 0x24;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801EFBF8 */
MATCH void BMagic_KaiserBreathDragonHover(void) {
    u8 count;

    Script_AnimStepLoop();
    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        Script_Select(1U);
        TASK(PartyMember)->unk_09 = 0x29;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801EFC74 */
MATCH void BMagic_KaiserBreathDragonBreathe(void) {
    PartyMember* battler;
    PartyMember* ring_battler;
    PartyMember* spark_battler;
    u8           i;
    u8           slot;
    u8           timer;

    Script_AnimStepOnce();
    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer != 0) {
        return;
    }
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x00));
    func_800A9610(g_Battle.target_selector, 16);
    slot                               = Battle_AllocEffect(1, 0x69) & BYTE_MASK;
    battler                            = g_BattleEffectBattler;
    g_BattleEffects[slot].header.mode  = KAISER_BREATH_EFFECT_RINGS;
    g_BattleEffects[slot].target.party = battler;
    g_BattleEffectBattler->param.unk_0B += 1;
    slot                               = Battle_AllocEffect(1, 0x69) & BYTE_MASK;
    battler                            = g_BattleEffectBattler;
    g_BattleEffects[slot].header.mode  = KAISER_BREATH_EFFECT_BEAM;
    g_BattleEffects[slot].target.party = battler;
    g_BattleEffectBattler->param.unk_0B += 1;
    for (i = 0; i < KAISER_BREATH_ORB_COUNT; i++) {
        slot = BMagic_KaiserBreathAllocParticle();
        if (slot == GAME_NONE) {
            continue;
        }
        ring_battler                                    = g_BattleEffectBattler;
        g_BMagicKaiserBreathParticles[slot].header.mode = KAISER_BREATH_PARTICLE_ORB;
        g_BMagicKaiserBreathParticles[slot].header.step = 0;
        g_BMagicKaiserBreathParticles[slot].unk_07      = i;
        g_BMagicKaiserBreathParticles[slot].battler     = ring_battler;
        g_BattleEffectBattler->param.unk_0B += 1;
    }
    for (i = 0; i < KAISER_BREATH_SPARK_COUNT; i++) {
        slot = BMagic_KaiserBreathAllocParticle();
        if (slot == GAME_NONE) {
            continue;
        }
        spark_battler                                   = g_BattleEffectBattler;
        g_BMagicKaiserBreathParticles[slot].header.mode = KAISER_BREATH_PARTICLE_SPARK;
        g_BMagicKaiserBreathParticles[slot].header.step = 0;
        g_BMagicKaiserBreathParticles[slot].unk_07      = i;
        g_BMagicKaiserBreathParticles[slot].battler     = spark_battler;
        g_BMagicKaiserBreathParticles[slot].unk_26      = (i < 16) ? ((i & 0xF) >> 1) + 1 : (i & 0xF) + 1;
        g_BattleEffectBattler->param.unk_0B += 1;
    }
    TASK(PartyMember)->header.step++;
}

/* func_801EFEF0 */
MATCH void BMagic_KaiserBreathDragonBreatheEnd(void) {
    if (Script_AnimStepOnce() != 0u) {
        TASK(PartyMember)->unk_09      = 0xF;
        TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
    }
}

/* func_801EFF48 */
MATCH void BMagic_KaiserBreathDragonLeave(void) {
    u32 direction;
    u8  timer;

    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        direction = LOBU(g_Battle.scroll_dir);
        if (direction == 0 || direction == 3) {
            TASK(PartyMember)->unk_0C = 8;
            TASK(PartyMember)->unk_10 = -1;
            TASK(PartyMember)->unk_18 = 1;
            TASK(PartyMember)->unk_1C = -1;
        } else {
            TASK(PartyMember)->unk_0C = -8;
            TASK(PartyMember)->unk_10 = -1;
            TASK(PartyMember)->unk_18 = -1;
            TASK(PartyMember)->unk_1C = -1;
        }
        TASK(PartyMember)->unk_09 = 0;
        TASK(PartyMember)->timer  = 30;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801F0034 */
MATCH void BMagic_KaiserBreathDragonEnd(void) {
    u8           timer;
    u8           count;
    PartyMember* work;

    if (g_FrameCount & 0x1) {
        count = TASK(PartyMember)->unk_09;
        if (count < 8U) {
            TASK(PartyMember)->unk_09 = count + 1;
            TASK(PartyMember)->unk_10 += TASK(PartyMember)->unk_1C;
        }
    }
    work        = TASK(PartyMember);
    timer       = work->timer - 1;
    work->timer = timer;
    work->screen_x.value += work->unk_0C;
    work->screen_y.value += work->unk_10;
    if (!(timer & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

/* func_801F0100 */
MATCH void BMagic_KaiserBreathRunFlash(void) {
    SYS_DISPATCH_BYTE(g_BMagicKaiserBreathFlashSteps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        BMagic_KaiserBreathDrawFlash();
    }
}

#include "overlays/bmagic/shared/Effect_ClearTimerNextStep.h"

#include "overlays/bmagic/shared/Effect_CountUpByTwoAndStep.h"

/* func_801F01F8 */
MATCH void BMagic_KaiserBreathFlashHold(void) {
    if ((BATTLE_ACTIVE_WORK->unk_09 == 0) && (EMI_IsReady() != 0)) {
        TASK(PartyMember)->timer = 8;
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_CountDownAndStep.h"

#include "overlays/bmagic/shared/Effect_TickOnTimerZero.h"

#include "overlays/bmagic/shared/Effect_DrawFullScreenQuad.h"

/* func_801F030C */
MATCH void BMagic_KaiserBreathDrawFlash(void) {
    POLY_F4* prim;
    s32      shade;
    s32      tpage;

    EFFECT_DRAW_FULL_SCREEN_QUAD(BMAGIC_LAYER_FOREGROUND);
}

/* func_801F0438 */
MATCH void BMagic_KaiserBreathRunRings(void) {
    BMAGIC_DISPATCH_AND_DRAW(g_BMagicKaiserBreathRingsSteps, BMagic_KaiserBreathDrawRings);
}

/* func_801F04C0 */
MATCH void BMagic_KaiserBreathRingsStart(void) {
    PartyMember* work;
    PartyMember* active;
    s32          x;
    s32          z;

    work              = TASK(PartyMember);
    x                 = g_AreaScrollTargetX;
    active            = g_BattleEffectBattler;
    work->pos.x.fixed = x;
    /* FAKE: Preserve the X write before the Y read. */
    FAKE_BARRIER();
    work->pos.y.fixed              = g_AreaScrollTargetY;
    z                              = active->pos.z.fixed;
    work->unk_5D                   = 16;
    work->pos.z.fixed              = z;
    TASK(PartyMember)->unk_09      = 32;
    TASK(PartyMember)->timer       = 8;
    TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
}

/* func_801F053C */
MATCH void BMagic_KaiserBreathRingsGrow(void) {
    EFFECT_ADVANCE_AT_COUNT(4, 0x40);
}

/* func_801F058C */
MATCH void BMagic_KaiserBreathRingsEnd(void) {
    PartyMember* work;
    PartyMember* active;
    s8           count;

    work = TASK(PartyMember);
    work->unk_09 += 2;
    work         = TASK(PartyMember);
    count        = work->unk_5D - 4;
    work->unk_5D = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->param.unk_0B--;
        Effect_Reset();
    }
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

/* Draws the effect as 8 rings of 16 textured quads around the party member. */
/* func_801F06B4 */
MATCH void BMagic_KaiserBreathDrawRings(void) {
    POLY_FT4* poly;
    long      depth;
    long      flag;
    s32       tpage;
    u8        ring;
    u8        i;
    s16       angle;

    tpage = getTPage(0, 1, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_EFFECT, tpage);

    g_ScratchPad.cells.halves[4] = (s8)TASK(PartyMember)->unk_5D * 8;
    g_ScratchPad.cells.halves[5] = (s8)TASK(PartyMember)->unk_5D * 8;
    g_ScratchPad.cells.halves[6] = (s8)TASK(PartyMember)->unk_5D * 8;
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->timer * 16;
    g_ScratchPad.cells.halves[1] = TASK(PartyMember)->unk_09 * 16;
    g_ScratchPadVectors[1].vz    = -FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    for (ring = 1; ring < 9; ring++) {
        g_ScratchPad.cells.halves[2] = g_ScratchPad.cells.halves[1];
        g_ScratchPad.cells.halves[1] = g_ScratchPad.cells.halves[2] - 0x40;
        g_ScratchPadVectors[3].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[2]);
        g_ScratchPadVectors[3].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[2]);
        g_ScratchPadVectors[2].vz    = g_ScratchPadVectors[1].vz;
        g_ScratchPadVectors[3].vz    = g_ScratchPadVectors[1].vz;
        g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[0].vz    = -FIXED_MUL(rsin(ring << 8), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vz    = g_ScratchPadVectors[0].vz;
        for (i = 1; i < 17; i++) {
            angle = i;
            angle &= 0xF;
            g_ScratchPad.cells.halves[3] = angle << 8;
            g_ScratchPadVectors[0].vx    = g_ScratchPadVectors[1].vx;
            g_ScratchPadVectors[0].vy    = g_ScratchPadVectors[1].vy;
            g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(angle << 8), g_ScratchPad.cells.halves[1]);
            g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[1]);
            g_ScratchPadVectors[2].vx    = g_ScratchPadVectors[3].vx;
            g_ScratchPadVectors[2].vy    = g_ScratchPadVectors[3].vy;
            g_ScratchPadVectors[3].vx    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[2]);
            g_ScratchPadVectors[3].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[2]);
            poly                         = (POLY_FT4*)g_GfxPrimCursor;
            SetPolyFT4(poly);
            SetSemiTrans(poly, 1);
            poly->tpage = GetTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 0x340, 0x100);
            poly->clut  = GetClut(0, 0x1FA);
            setUV4(poly, ((i & 1) + (ring - 1) / 4 * 2) << 6, g_BMagicRingUvRows[0xB + ring], (((i & 1) + (ring - 1) / 4 * 2) << 6) + 0x3F, g_BMagicRingUvRows[0xB + ring],
                   ((i & 1) + (ring - 1) / 4 * 2) << 6, g_BMagicRingUvRows[0x13 + ring] - 1 + g_BMagicRingUvRows[0xB + ring], (((i & 1) + (ring - 1) / 4 * 2) << 6) + 0x3F,
                   g_BMagicRingUvRows[0x13 + ring] - 1 + g_BMagicRingUvRows[0xB + ring]);
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&poly->x0, (long*)&poly->x1, (long*)&poly->x2, (long*)&poly->x3,
                          &depth, &flag);
            setRGB0(poly, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
            if ((u8)(i - 10) >= 2) {
                GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(POLY_FT4));
            }
        }
    }
}

/* func_801F0B44 */
MATCH void BMagic_KaiserBreathRunBeam(void) {
    BMAGIC_DISPATCH_AND_DRAW_IN_OWN_MATRIX(g_BMagicKaiserBreathBeamSteps, BMagic_KaiserBreathBeamSetMatrix, BMagic_KaiserBreathDrawBeam);
}

/* func_801F0BCC */
MATCH void BMagic_KaiserBreathBeamStart(void) {
    PartyMember* work;
    PartyMember* source;

    work              = TASK(PartyMember);
    source            = g_BattleEffectBattler;
    work->pos.x.fixed = g_AreaScrollTargetX;
    /* FAKE: Keep the Y load after the X store; the scheduler hoists it (without it 0x7C vs 0x80 bytes). */
    FAKE_BARRIER();
    work->pos.y.fixed         = g_AreaScrollTargetY;
    work->pos.z.fixed         = source->pos.z.fixed;
    work->unk_14              = 0x40;
    work->param.unk_0B        = 0;
    TASK(PartyMember)->unk_09 = 0x10;
    TASK(PartyMember)->timer  = 1;
    TASK(PartyMember)->header.step++;
}

/* func_801F0C4C */
MATCH void BMagic_KaiserBreathBeamGrow(void) {
    s32 radius;

    radius                    = TASK(PartyMember)->unk_14 + 0x20;
    TASK(PartyMember)->unk_14 = radius;
    if (radius == 0x200) {
        TASK(PartyMember)->param.unk_0B = 1;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void BMagic_KaiserBreathBeamHold(void) {
    BMAGIC_COUNT_DOWN_AND_STEP();
}

/* func_801F0CE4 */
MATCH void BMagic_KaiserBreathBeamEnd(void) {
    PartyMember* work = TASK(PartyMember);
    u8           timer;

    work->unk_14 += 0x10;

    timer        = work->unk_09 - 2;
    work->unk_09 = timer;
    if (timer == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

MATCH void BMagic_KaiserBreathBeamSetMatrix(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    BMAGIC_SET_ACTOR_MATRIX();
}

/* func_801F0DF4 */
MATCH void BMagic_KaiserBreathDrawBeam(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       tpage;
    s32       u;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TASK(PartyMember)->param.unk_0B, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->unk_14;
    g_ScratchPad.cells.halves[4] = TASK(PartyMember)->unk_09 << 3;
    g_ScratchPad.cells.halves[5] = TASK(PartyMember)->unk_09 << 3;
    g_ScratchPad.cells.halves[6] = TASK(PartyMember)->unk_09 << 3;
    g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
    for (i = 1; i <= 16; i++) {
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[0].vz = -1024;
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[2].vz = 0;
        g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(i << 8), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(i << 8), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vz = -1024;
        g_ScratchPadVectors[3].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[3].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[3].vz = 0;
        prim                      = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetSemiTrans(prim, TASK(PartyMember)->param.unk_0B);
        prim->tpage = GetTPage(TPAGE_DEPTH_8BIT, TASK(PartyMember)->param.unk_0B, 832, 256);
        prim->clut  = GetClut(0, 506);
        u           = (i & 1) << 6;
        setUV4(prim, u, 0, u + 63, 0, u, 191, u + 63, 191);
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        if (i < 7 || i > 14) {
            GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_FT4));
        }
    }
}

/* func_801F10F4 */
MATCH void BMagic_KaiserBreathRunParticle(void) {
    SYS_DISPATCH_TASK(g_BMagicKaiserBreathParticleModes, 1, g_BMagicKaiserBreathParticle);
}

/* func_801F1138 */
MATCH void BMagic_KaiserBreathRunOrb(void) {
    SYS_DISPATCH_BYTE(g_BMagicKaiserBreathOrbSteps, g_BMagicKaiserBreathParticle->header.step);
    if (g_BMagicKaiserBreathParticle->header.flags != 0 && g_BMagicKaiserBreathParticle->header.step != 0) {
        BMagic_KaiserBreathProjectParticle();
        BMagic_KaiserBreathDrawGlow();
    }
}

/* func_801F11B8 */
MATCH void BMagic_KaiserBreathOrbStart(void) {
    s16* angle_cell;
    s32  z;
    u8   phase;

    phase                                     = g_BMagicKaiserBreathOrbPhases[g_BMagicKaiserBreathParticle->unk_07];
    angle_cell                                = &D_1F800006;
    *angle_cell                               = phase << 7;
    g_BMagicKaiserBreathParticle->pos.x.fixed = g_AreaScrollTargetX + ((rsin(phase << 7) << 6) >> 3);
    g_BMagicKaiserBreathParticle->pos.y.fixed = g_AreaScrollTargetY + ((rcos(*angle_cell) << 6) >> 3);
    z                                         = g_BattleEffectBattler->pos.z.fixed;
    g_BMagicKaiserBreathParticle->pos.z.fixed = z;
    g_BMagicKaiserBreathParticle->phase_0C    = 0x40;
    g_BMagicKaiserBreathParticle->timer_05    = 16;
    g_BMagicKaiserBreathParticle->unk_06      = 20;
    g_BMagicKaiserBreathParticle->header.step++;
}

/* func_801F12A0 */
MATCH void BMagic_KaiserBreathOrbGrow(void) {
    s16* angle_cell;
    u8   phase;

    MAGIC131_ORBIT_GROW(g_BMagicKaiserBreathOrbPhases, 7);
}

/* func_801F13A4 */
MATCH void BMagic_KaiserBreathOrbEnd(void) {
    s16* angle_cell;
    u8   phase;
    u8   timer;

    MAGIC131_ORBIT_CLOSE(g_BMagicKaiserBreathOrbPhases, 7);
}

/* func_801F14A0 */
MATCH void BMagic_KaiserBreathRunSpark(void) {
    s16 timer;

    SYS_DISPATCH_BYTE(g_BMagicKaiserBreathSparkSteps, g_BMagicKaiserBreathParticle->header.step);
    timer = g_BMagicKaiserBreathParticle->unk_26;
    if (timer != 0) {
        g_BMagicKaiserBreathParticle->unk_26 = timer - 1;
        return;
    }
    if (g_BMagicKaiserBreathParticle->header.flags != 0 && g_BMagicKaiserBreathParticle->header.step != 0) {
        BMagic_KaiserBreathProjectParticle();
        BMagic_KaiserBreathDrawGlow();
    }
}

/* func_801F153C */
MATCH void BMagic_KaiserBreathSparkStart(void) {
    s16* angle_cell;
    u8   phase;

    phase                                     = g_BMagicKaiserBreathSparkPhases[g_BMagicKaiserBreathParticle->unk_07];
    angle_cell                                = &D_1F800006;
    *angle_cell                               = phase << 6;
    g_BMagicKaiserBreathParticle->pos.x.fixed = g_AreaScrollTargetX + ((rsin(phase << 6) << 6) >> 3);
    g_BMagicKaiserBreathParticle->pos.y.fixed = g_AreaScrollTargetY + ((rcos(*angle_cell) << 6) >> 3);
    g_BMagicKaiserBreathParticle->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    COORD_INT(g_BMagicKaiserBreathParticle->pos.z) += g_BMagicKaiserBreathSparkDepths[g_BMagicKaiserBreathParticle->unk_07] << 6;
    g_BMagicKaiserBreathParticle->phase_0C = 0x40;
    g_BMagicKaiserBreathParticle->timer_05 = 16;
    g_BMagicKaiserBreathParticle->unk_06   = 8;
    g_BMagicKaiserBreathParticle->header.step += 1;
}

/* func_801F1644 */
MATCH void BMagic_KaiserBreathSparkGrow(void) {
    s16* angle_cell;
    u8   phase;

    MAGIC131_ORBIT_GROW(g_BMagicKaiserBreathSparkPhases, 6);
}

/* func_801F1748 */
MATCH void BMagic_KaiserBreathSparkEnd(void) {
    s16* angle_cell;
    u8   phase;
    u8   timer;

    MAGIC131_ORBIT_CLOSE(g_BMagicKaiserBreathSparkPhases, 6);
}

/* func_801F1844 */
MATCH void BMagic_KaiserBreathDrawGlow(void) {
    POLY_G3* prim;
    s32      shade;
    u8       i;

    g_ScratchPad.cells.halves[0] = g_BMagicKaiserBreathParticle->unk_06 + (rand() & 3);
    if (g_BMagicKaiserBreathParticle->header.mode != 0) {
        shade = ((rand() & 3) + 4) * g_BMagicKaiserBreathParticle->timer_05;
    } else {
        shade = g_BMagicKaiserBreathParticle->timer_05 * 14;
    }
    g_ScratchPad.cells.halves[6] = g_BMagicKaiserBreathParticle->unk_20;
    g_ScratchPad.cells.halves[7] = g_BMagicKaiserBreathParticle->unk_22;
    for (i = 0; i < 8; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7]);
        g_ScratchPad.cells.halves[3] = (i << 9) & ANGLE_MASK;
        prim->x1                     = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[0]);
        prim->y1                     = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[0]);
        g_ScratchPad.cells.halves[3] = ((i + 1) << 9) & ANGLE_MASK;
        prim->x2                     = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[0]);
        prim->y2                     = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[0]);
        setRGB0(prim, shade, shade, shade);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_G3));
    }
}

/* func_801F1A58 */
MATCH u8 BMagic_KaiserBreathAllocParticle(void) {
    u8 i;

    for (i = 0; i < KAISER_BREATH_PARTICLE_COUNT; i++) {
        if (!(g_BMagicKaiserBreathParticles[i].header.flags & BMAGIC_EFFECT_IN_USE)) {
            g_BMagicKaiserBreathParticles[i].header.flags |= BMAGIC_EFFECT_IN_USE;
            return i;
        }
    }
    return GAME_NONE;
}

/* func_801F1AC4 */
MATCH void BMagic_KaiserBreathFreeParticle(void) {
    g_BMagicKaiserBreathParticle->header.flags = 0;
    g_BMagicKaiserBreathParticle->header.mode  = 0;
    g_BMagicKaiserBreathParticle->header.step  = 0;
    g_BMagicKaiserBreathParticle->unk_03       = 0;
    g_BMagicKaiserBreathParticle->unk_04       = 0;
}

/* func_801F1B14 */
MATCH void BMagic_KaiserBreathProjectParticle(void) {
    BMagicEffect* work;
    s16           vec[3];
    TILE_1*       primitive;

    work      = g_BMagicKaiserBreathParticle;
    vec[0]    = (work->pos.x.fixed >> 9) - AREA_CELL_ORIGIN;
    primitive = (TILE_1*)g_GfxPrimCursor;
    vec[1]    = (work->pos.y.fixed >> 9) - AREA_CELL_ORIGIN;
    vec[2]    = -(COORD_INT(work->pos.z) / 2);
    SetTile1(primitive);
    RotTransPers((SVECTOR*)vec, (long*)&primitive->x0, (long*)vec, (long*)&vec[2]);
    g_BMagicKaiserBreathParticle->unk_20 = primitive->x0;
    g_BMagicKaiserBreathParticle->unk_22 = primitive->y0;
}
