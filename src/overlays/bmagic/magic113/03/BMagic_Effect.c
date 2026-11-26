#include "magic113_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEC24 */
MATCH void BMagic_NotingUpdate(void) {
    BMagicNotingSteps handlers;

    BMAGIC_DISPATCH_STEP_HANDLERS(g_BMagicNotingSteps, header.mode);
    BMAGIC_DRAW_IF_ALIVE(BMagic_NotingDrawShadow);
}

/* func_801EECE0 */
MATCH void BMagic_NotingInit(void) {
    u8   i;
    u16* dst;
    u16* src;

    if ((g_Battle.target_selector < BATTLE_PARTY_CHARACTERS_COUNT && g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) ||
        (g_Battle.target_selector >= BATTLE_PARTY_CHARACTERS_COUNT && g_Battle.active_battler >= BATTLE_PARTY_CHARACTERS_COUNT)) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
    } else {
        i = 0;
        WorldPos_Copy(&TASK(PartyMember)->pos, &g_Battle.selected_actor->pos);
        dst = g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
        src = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
        for (; i < 16; i++) {
            dst[i] = src[i] | PSX_COLOR_STP_BIT;
        }
        g_GfxPalettePending             = 1;
        TASK(PartyMember)->param.unk_0B = 0;
        TASK(PartyMember)->unk_09       = 0;
        TASK(PartyMember)->header.mode += 1;
    }
}

/* func_801EEE24 */
MATCH void BMagic_NotingSpawnRings(void) {
    u8           timer;
    u32          slot;
    PartyMember* work;
    u8           facing;

    timer                     = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 16) {
        slot                                   = Battle_AllocEffect(1, 3) & BYTE_MASK;
        work                                   = TASK(PartyMember);
        g_BattleEffects[slot].header.mode      = BMAGIC_NOTING_EFFECT_RING;
        g_BattleEffects[slot].unk_0B           = 0;
        g_BattleEffects[slot].target.party     = work;
        facing                                 = g_BattleEffectBattler->facing;
        g_BattleEffects[slot].arg.unk_09       = 0;
        g_BattleEffects[slot].unk_0A           = 0;
        g_BattleEffects[slot].unk_08           = (facing + 2) & 3;
        g_BattleEffects[slot].pos.x            = TASK(PartyMember)->pos.x;
        g_BattleEffects[slot].pos.y            = TASK(PartyMember)->pos.y;
        COORD_INT(g_BattleEffects[slot].pos.z) = COORD_INT(TASK(PartyMember)->pos.z);
        slot                                   = Battle_AllocEffect(1, 3) & BYTE_MASK;
        work                                   = TASK(PartyMember);
        g_BattleEffects[slot].header.mode      = BMAGIC_NOTING_EFFECT_RING;
        g_BattleEffects[slot].unk_0B           = 1;
        g_BattleEffects[slot].target.party     = work;
        facing                                 = g_BattleEffectBattler->facing;
        g_BattleEffects[slot].arg.unk_09       = 0;
        g_BattleEffects[slot].unk_0A           = 0;
        g_BattleEffects[slot].unk_08           = (facing + 2) & 3;
        g_BattleEffects[slot].pos.x            = TASK(PartyMember)->pos.x;
        g_BattleEffects[slot].pos.y            = TASK(PartyMember)->pos.y;
        COORD_INT(g_BattleEffects[slot].pos.z) = COORD_INT(TASK(PartyMember)->pos.z);
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        TASK(PartyMember)->header.mode += 1;
    }
}

/* BMagic_NotingSpawnStar */
/* func_801EF000 */
MATCH void BMagic_NotingSpawnStar(void) {
    u32          slot;
    PartyMember* work;
    u8           facing;

    if (TASK(PartyMember)->param.unk_0B == BMAGIC_NOTING_STAGE_RINGS) {
        BMAGIC_NOTING_SPAWN_EFFECT(BMAGIC_NOTING_EFFECT_STAR);
    }
}

/* func_801EF0F0 */
MATCH void BMagic_NotingSpawnWall(void) {
    u32          slot;
    PartyMember* work;
    u8           facing;

    if (TASK(PartyMember)->param.unk_0B == BMAGIC_NOTING_STAGE_STAR) {
        BMAGIC_NOTING_SPAWN_EFFECT(BMAGIC_NOTING_EFFECT_WALL);
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0x02));
        g_SndVoiceTargetVolume[20] = 0x7F;
        g_SndVoiceVolume[20]       = 0;
    }
}

/* func_801EF1F8 */
MATCH void BMagic_NotingSpawnActors(void) {
    u8           i;
    u32          slot;
    PartyMember* work;
    u8           facing;

    SND_VoiceDecreaseTargetVolume(20, 16);
    SND_StartVolumeSweep(20);
    if (TASK(PartyMember)->param.unk_0B == BMAGIC_NOTING_STAGE_WALL) {
        for (i = 0; i < 6; i++) {
            slot                                   = Battle_AllocEffect(1, 3) & BYTE_MASK;
            work                                   = TASK(PartyMember);
            g_BattleEffects[slot].header.mode      = BMAGIC_NOTING_EFFECT_ACTOR;
            g_BattleEffects[slot].unk_04           = i & 1;
            g_BattleEffects[slot].target.party     = work;
            facing                                 = g_BattleEffectBattler->facing;
            g_BattleEffects[slot].arg.unk_09       = (i >> 1) * 8 + 1;
            g_BattleEffects[slot].unk_0A           = 0;
            g_BattleEffects[slot].unk_0B           = i >> 1;
            g_BattleEffects[slot].unk_08           = (facing + 2) & 3;
            g_BattleEffects[slot].pos.x            = TASK(PartyMember)->pos.x;
            g_BattleEffects[slot].pos.y            = TASK(PartyMember)->pos.y;
            COORD_INT(g_BattleEffects[slot].pos.z) = COORD_INT(TASK(PartyMember)->pos.z);
        }
        TASK(PartyMember)->param.unk_0B = 0;
        TASK(PartyMember)->header.mode += 1;
    }
}

/* func_801EF35C */
MATCH void BMagic_NotingRelease(void) {
    if (TASK(PartyMember)->param.unk_0B == BMAGIC_NOTING_STAGE_ACTORS) {
        TASK(PartyMember)->param.unk_0B = BMAGIC_NOTING_STAGE_RELEASE;
        TASK(PartyMember)->header.mode += 1;
    }
}

/* func_801EF3A0 */
MATCH void BMagic_NotingWait(void) {
    PartyMember* work;

    work = TASK(PartyMember);
    if (work->param.unk_0B == BMAGIC_NOTING_STAGE_RELEASED) {
        work->header.mode = (work->header.mode + 1);
    }
}

#include "overlays/bmagic/shared/Effect_CountDownAndMarkDamaged.h"

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

/* func_801EF4F0 */
MATCH void BMagic_NotingDrawShadow(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    s_BMagicNotingRadius      = 0x1C0;
    g_ScratchPadVectors[2].vx = FIXED_MUL(rsin(0), s_BMagicNotingRadius);
    g_ScratchPadVectors[2].vy = FIXED_MUL(rcos(0), s_BMagicNotingRadius);
    for (i = 1; i <= 32; i++) {
        prim                      = GFX_BeginPolyG3(1);
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = 0;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy;
        setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(i << 7), s_BMagicNotingRadius), FIXED_MUL(rcos(i << 7), s_BMagicNotingRadius), 0);
        g_ScratchPadVectors[1].vz = 0;
        g_ScratchPadVectors[0].vz = 0;
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        g_ScratchPad.cells.words[1] = TASK(PartyMember)->unk_09 * 12;
        setRGB0(prim, g_ScratchPad.cells.words[1], g_ScratchPad.cells.words[1], g_ScratchPad.cells.words[1]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

/* func_801EF75C */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

/* func_801EF7A0 */
MATCH void BMagic_NotingRingUpdate(void) {
    SYS_DISPATCH_BYTE(g_BMagicNotingRingSteps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0) {
        Effect_SetActorMatrix();
        s_BMagicNotingRadius = g_BMagicNotingRingRadii[TASK(PartyMember)->param.unk_0B];
        BMagic_NotingDrawRing();
        PopMatrix();
    }
}

/* func_801EF844 */
MATCH void BMagic_NotingRingGrow(void) {
    u8 count;

    count                     = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 0x21) {
        g_BattleEffectBattler->param.unk_0B = BMAGIC_NOTING_STAGE_RINGS;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801EF8A4 */
MATCH void BMagic_NotingRingHold(void) {
    PartyMember* active;
    PartyMember* work;

    BMAGIC_NOTING_ADVANCE_AT_STAGE(BMAGIC_NOTING_STAGE_RELEASE);
}

/* func_801EF8E4 */
MATCH void BMagic_NotingRingFade(void) {
    Effect_CountUpTimer();
}

/* func_801EF944 */
MATCH void BMagic_NotingDrawRing(void) {
    LINE_F2* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    setVector(&g_ScratchPadVectors[0], FIXED_MUL(rsin(0), s_BMagicNotingRadius), FIXED_MUL(rcos(0), s_BMagicNotingRadius), 0);
    for (i = 1; i <= 32; i++) {
        if (i < TASK(PartyMember)->unk_09) {
            prim = (LINE_F2*)g_GfxPrimCursor;
            SetLineF2(prim);
            if (TASK(PartyMember)->header.step == 2) {
                SetSemiTrans(prim, 1);
            }
            RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x0, &depth, &flag);
            setVector(&g_ScratchPadVectors[0], FIXED_MUL(rsin(i << 7), s_BMagicNotingRadius), FIXED_MUL(rcos(i << 7), s_BMagicNotingRadius), 0);
            RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x1, &depth, &flag);
            setRGB0(prim, 240, 170, 200);
            if (TASK(PartyMember)->header.step == 2) {
                setRGB0(prim, 240 - TASK(PartyMember)->timer * 20, 170 - TASK(PartyMember)->timer * 14, 200 - TASK(PartyMember)->timer * 16);
            }
            GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(LINE_F2));
        }
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

/* func_801EFC28 */
MATCH void BMagic_NotingStarUpdate(void) {
    SYS_DISPATCH_BYTE(g_BMagicNotingStarSteps, TASK(PartyMember)->header.step);
    BMAGIC_DRAW_IF_ALIVE(BMagic_NotingDrawStar);
}

/* func_801EFCA0 */
MATCH void BMagic_NotingStarGrow(void) {
    u8 count;

    count                     = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 0x28) {
        g_BattleEffectBattler->param.unk_0B = BMAGIC_NOTING_STAGE_STAR;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801EFD00 */
MATCH void BMagic_NotingStarHold(void) {
    PartyMember* active;
    PartyMember* work;

    BMAGIC_NOTING_ADVANCE_AT_STAGE(BMAGIC_NOTING_STAGE_RELEASE);
}

/* func_801EFD40 */
MATCH void BMagic_NotingStarFade(void) {
    Effect_CountUpTimer();
}

/* func_801EFDA0 */
MATCH void BMagic_NotingDrawStar(void) {
    LINE_F2* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      length;
    s32      left;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    for (i = 0; i < 5; i++) {
        if (i * 8 < TASK(PartyMember)->unk_09) {
            left   = TASK(PartyMember)->unk_09 - i * 8;
            length = 8;
            if (left < 8) {
                length = left;
            }
            prim = (LINE_F2*)g_GfxPrimCursor;
            SetLineF2(prim);
            if (TASK(PartyMember)->header.step == 2) {
                SetSemiTrans(prim, 1);
            }
            g_ScratchPadVectors[0].vx = FIXED_MUL(rsin(g_BMagicNotingStarCorners[i] * 273), 288);
            g_ScratchPadVectors[0].vy = FIXED_MUL(rcos(g_BMagicNotingStarCorners[i] * 273), 288);
            g_ScratchPadVectors[0].vz = 0;
            RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x0, &depth, &flag);
            g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(g_BMagicNotingStarCorners[i + 1] * 273), 288);
            g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(g_BMagicNotingStarCorners[i + 1] * 273), 288);
            setVector(&g_ScratchPadVectors[1], g_ScratchPadVectors[0].vx + ((g_ScratchPadVectors[1].vx - g_ScratchPadVectors[0].vx) / 8) * length,
                      g_ScratchPadVectors[0].vy + ((g_ScratchPadVectors[1].vy - g_ScratchPadVectors[0].vy) / 8) * length, 0);
            RotTransPers(&g_ScratchPadVectors[1], (long*)&prim->x1, &depth, &flag);
            setRGB0(prim, 240, 170, 200);
            if (TASK(PartyMember)->header.step == 2) {
                setRGB0(prim, 240 - TASK(PartyMember)->timer * 20, 170 - TASK(PartyMember)->timer * 14, 200 - TASK(PartyMember)->timer * 16);
            }
            GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(LINE_F2));
        }
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

/* func_801F0140 */
MATCH void BMagic_NotingWallUpdate(void) {
    SYS_DISPATCH_BYTE(g_BMagicNotingWallSteps, TASK(PartyMember)->header.step);
    BMAGIC_DRAW_IF_ALIVE(BMagic_NotingDrawWall);
}

/* func_801F01B8 */
MATCH void BMagic_NotingWallRise(void) {
    u8 count;

    count                     = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 0x31) {
        g_BattleEffectBattler->param.unk_0B = BMAGIC_NOTING_STAGE_WALL;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801F0218 */
MATCH void BMagic_NotingWallHold(void) {
    if (g_BattleEffectBattler->param.unk_0B == BMAGIC_NOTING_STAGE_RELEASE) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0x03));
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801F026C */
MATCH void BMagic_NotingWallFade(void) {
    PartyMember* work;
    u8           next;

    work        = TASK(PartyMember);
    next        = work->timer + 1;
    work->timer = next;
    if (next == 0x10) {
        BATTLE_ACTIVE_WORK->param.unk_0B--;
        Effect_Reset();
    }
}

/* func_801F02CC */
MATCH void BMagic_NotingDrawWall(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      x;
    s32      y;
    s32      tpage;

    if (TASK(PartyMember)->unk_09 < 16) {
        g_ScratchPad.cells.words[2] = TASK(PartyMember)->unk_09 * 32;
    } else {
        g_ScratchPad.cells.words[2] = 0x200;
    }
    setVector(&g_ScratchPadVectors[1], FIXED_MUL(rcos(0), 304), FIXED_MUL(rsin(0), 304), TASK(PartyMember)->timer * 8 - g_ScratchPad.cells.words[2]);
    setVector(&g_ScratchPadVectors[3], FIXED_MUL(rcos(0), 304), FIXED_MUL(rsin(0), 304), 0);
    for (i = 1; i <= 32; i++) {
        if (i < TASK(PartyMember)->unk_09) {
            if (TASK(PartyMember)->unk_09 - i < 16) {
                g_ScratchPad.cells.words[2] = (TASK(PartyMember)->unk_09 - i) * 32;
            } else {
                g_ScratchPad.cells.words[2] = (rand() & 0x3F) + 0x200;
                if (i == 32) {
                    g_ScratchPad.cells.words[2] = 0x200;
                }
            }
            g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
            g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
            g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz;
            g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
            g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
            g_ScratchPadVectors[2].vz = 0;
            setVector(&g_ScratchPadVectors[1], FIXED_MUL(rcos(i << 7), 304), FIXED_MUL(rsin(i << 7), 304), TASK(PartyMember)->timer * 8 - g_ScratchPad.cells.words[2]);
            g_ScratchPadVectors[3].vx = FIXED_MUL(rcos(i << 7), 304);
            g_ScratchPadVectors[3].vy = FIXED_MUL(rsin(i << 7), 304);
            g_ScratchPadVectors[3].vz = 0;
            x                         = (g_ScratchPadVectors[3].vx << 9) + TASK(PartyMember)->pos.x.fixed;
            y                         = (g_ScratchPadVectors[3].vy << 9) + TASK(PartyMember)->pos.y.fixed;
            tpage                     = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
            Area_CellAddPrim(x, y, 0, sizeof(DR_MODE));
            prim = (POLY_G4*)g_GfxPrimCursor;
            SetPolyG4(prim);
            SetSemiTrans(prim, 1);
            g_ScratchPad.cells.words[1] = 32 - TASK(PartyMember)->timer * 2;
            setRGB0(prim, 1, 1, 1);
            setRGB1(prim, 1, 1, 1);
            setRGB2(prim, 192 - TASK(PartyMember)->timer * 12, g_ScratchPad.cells.words[1], g_ScratchPad.cells.words[1]);
            setRGB3(prim, 192 - TASK(PartyMember)->timer * 12, g_ScratchPad.cells.words[1], g_ScratchPad.cells.words[1]);
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                          &depth, &flag);
            Area_CellAddPrim(x, y, 0, sizeof(POLY_G4));
        }
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
}

/* func_801F0764 */
MATCH void BMagic_NotingActorUpdate(void) {
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256));
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(g_BMagicNotingActorSteps, TASK(PartyMember)->header.step);
    g_Scripts = AREA_SCRIPT_TABLE;
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256));
}

#include "overlays/bmagic/shared/Effect_CountDownTimerStep.h"

/* func_801F08B4 */
MATCH void BMagic_NotingActorPlace(void) {
    PartyMember* task;
    s8           tint;

    TASK(PartyMember)->pos.x.fixed        = TASK(PartyMember)->pos.x.fixed;
    TASK(PartyMember)->pos.y.fixed        = TASK(PartyMember)->pos.y.fixed;
    TASK(PartyMember)->pos.z.part.integer = (s16)TASK(PartyMember)->pos.z.part.integer;
    if (TASK(PartyMember)->param.unk_0B == 2) {
        TASK(PartyMember)->pos.z.fixed += 0x01800000;
    }
    if (TASK(PartyMember)->unk_04 != 0) {
        TASK(PartyMember)->pos.z.fixed += 0x02000000;
    }
    TASK(PartyMember)->unk_25 = 0x1D;
    TASK(PartyMember)->unk_26 = 0;
    TASK(PartyMember)->unk_27 = 0xA0;
    TASK(PartyMember)->unk_28 = 0;
    TASK(PartyMember)->header.flags |= 0x20;
    tint                      = -0x40;
    TASK(PartyMember)->unk_5D = tint;
    TASK(PartyMember)->unk_5E = tint;
    TASK(PartyMember)->unk_5F = tint;
    TASK(PartyMember)->unk_5C = 1;
    TASK(PartyMember)->unk_2A = TASK(PartyMember)->unk_04;
    TASK(PartyMember)->unk_29 = 4;
    TASK(PartyMember)->unk_24 = 4;
    task                      = TASK(PartyMember);
    task->unk_2B              = 1;
    task->unk_2C.value        = 0;
    TASK(PartyMember)->unk_09 = 0;
    TASK(PartyMember)->header.step += 1;
    if (TASK(PartyMember)->param.unk_0B == 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0x00));
    }
    Script_Select(TASK(PartyMember)->param.unk_0B);
}

/* func_801F0A80 */
MATCH void BMagic_NotingActorPlay(void) {
    u8 value;

    if (Script_AnimStepOnce() & BYTE_MASK) {
        value                     = TASK(PartyMember)->unk_09 + 1;
        TASK(PartyMember)->unk_09 = value;
        if ((value & BYTE_MASK) >= 3U) {
            g_BattleEffectBattler->param.unk_0B += 1;
            Effect_Reset();
            return;
        }
        TASK(PartyMember)->unk_2A = (TASK(PartyMember)->unk_2A + 0x1) & 1;
        Script_Select(TASK(PartyMember)->param.unk_0B);
        Area_AddGridActor();
        if (TASK(PartyMember)->param.unk_0B == 0) {
            if (TASK(PartyMember)->unk_09 == 1) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0x04));
                return;
            }
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0x00));
        }
    } else {
        Area_AddGridActor();
    }
}
