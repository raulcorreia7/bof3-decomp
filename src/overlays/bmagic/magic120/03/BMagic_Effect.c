#include "magic120_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

/* Spawns the stream and the actors, copies the battle palette row and advances the task mode. */
/* func_801EEC70 */
MATCH void BMagic_WhelpBreathInit(void) {
    u32          slot;
    u32          i;
    PartyMember* work;
    PartyMember* battler;

    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&SELF(PartyMember)->pos, &g_BattleEffectBattler->pos);
    slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_WHELP_BREATH) & BYTE_MASK;
    work                               = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = BMAGIC_WHELP_BREATH_EFFECT_STREAM;
    g_BattleEffects[slot].arg.unk_09   = BMAGIC_WHELP_BREATH_AIM_DELAY;
    g_BattleEffects[slot].target.party = work;
    slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_WHELP_BREATH) & BYTE_MASK;
    battler                            = g_BattleEffectBattler;
    g_BattleEffects[slot].header.mode  = BMAGIC_WHELP_BREATH_EFFECT_ACTOR;
    g_BattleEffects[slot].unk_0B       = BMAGIC_WHELP_BREATH_ACTOR_PLAY;
    g_BattleEffects[slot].target.party = battler;
    if (!(SELF(PartyMember)->facing & 2)) {
        PartyMember* owner;

        slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_WHELP_BREATH) & BYTE_MASK;
        owner                              = g_BattleEffectBattler;
        g_BattleEffects[slot].header.mode  = BMAGIC_WHELP_BREATH_EFFECT_ACTOR;
        g_BattleEffects[slot].unk_0B       = BMAGIC_WHELP_BREATH_ACTOR_LOOP;
        g_BattleEffects[slot].target.party = owner;
    }
    {
        u16* row;
        u16* arena;

        for (i = 1, row = g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors + 1, arena = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors + 1; i < 16; i++) {
            *row++ = *arena++ | PSX_COLOR_STP_BIT;
        }
    }
    {
        u16* arena;
        u16* row;

        for (i = 1, arena = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors + 1, row = g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors + 1; i < 16; i++) {
            row[16] = arena[16];
            arena++;
            row++;
        }
    }
    {
        u16* arena;
        u16* row;

        for (i = 1, arena = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors + 1, row = g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors + 1; i < 16; i++) {
            row[32] = arena[32] | PSX_COLOR_STP_BIT;
            arena++;
            row++;
        }
    }
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0]  = 0;
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[16] = 0;
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[32] = 0;
    g_GfxPalettePending                                           = 1;
    SELF(PartyMember)->param.unk_0B                               = 0;
    SELF(PartyMember)->unk_09                                     = 0;
    SELF(PartyMember)->header.mode += 1;
}

/* Once the stream has grown (task byte 0x0B is 1), spawns the puff and shade actors. */
/* func_801EEEC8 */
MATCH void BMagic_WhelpBreathWaitGrown(void) {
    u32          slot;
    PartyMember* task;
    PartyMember* task2;

    if (SELF(PartyMember)->param.unk_0B == BMAGIC_WHELP_BREATH_GROWN) {
        slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_WHELP_BREATH) & BYTE_MASK;
        task                               = SELF(PartyMember);
        g_BattleEffects[slot].header.mode  = BMAGIC_WHELP_BREATH_EFFECT_ACTOR;
        g_BattleEffects[slot].unk_0B       = BMAGIC_WHELP_BREATH_ACTOR_PUFFS;
        g_BattleEffects[slot].target.party = task;
        slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_WHELP_BREATH) & BYTE_MASK;
        task2                              = SELF(PartyMember);
        g_BattleEffects[slot].header.mode  = BMAGIC_WHELP_BREATH_EFFECT_ACTOR;
        g_BattleEffects[slot].unk_0B       = BMAGIC_WHELP_BREATH_ACTOR_SHADE;
        g_BattleEffects[slot].target.party = task2;
        SELF(PartyMember)->header.mode += 1;
    }
}

#include "overlays/bmagic/shared/Effect_PlayOnIdleTick.h"

/* func_801EF010 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

/* Runs the stream step that header.step selects and draws the stream once it has started, until the task's byte 0x0B is 0xFF. */
/* func_801EF054 */
MATCH void BMagic_WhelpBreathStreamUpdate(void) {
    SYS_DISPATCH_BYTE(g_BMagicWhelpBreathStreamSteps, SELF(PartyMember)->header.step);
    if (g_BattleEffectBattler->param.unk_0B != 0xFF) {
        if (SELF(PartyMember)->header.step != 0) {
            BMagic_WhelpBreathDrawStream();
        }
    }
}

/* Stream step 0: after the aim delay, projects the stream from the camera centre to the battler, offset by unk_0C and
 * unk_10 on screen, and aims it along the screen line between the two points the scratchpad keeps. */
/* func_801EF0D8 */
MATCH void BMagic_WhelpBreathStreamStart(void) {
    u8           timer;
    PartyMember* work;
    s32          angle;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
        Battle_CenterCamera();
        Battle_ProjectRange();
        g_ScratchPad.cells.halves[6] = SELF(PartyMember)->screen_x.value;
        g_ScratchPad.cells.halves[7] = SELF(PartyMember)->screen_y.value;
        func_800B0118();
        WorldPos_Copy(&SELF(PartyMember)->pos, &g_BattleEffectBattler->pos);
        Battle_ProjectRange();
        SELF(PartyMember)->screen_x.value += SELF(PartyMember)->unk_0C;
        SELF(PartyMember)->screen_y.value += SELF(PartyMember)->unk_10;
        g_ScratchPad.cells.halves[4] = SELF(PartyMember)->screen_x.value;
        g_ScratchPad.cells.halves[5] = SELF(PartyMember)->screen_y.value;
        angle                        = ratan2(g_ScratchPad.cells.halves[6] - g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[7] - g_ScratchPad.cells.halves[5]);
        work                         = SELF(PartyMember);
        work->param.unk_0B           = 17;
        work->unk_14                 = angle;
        SELF(PartyMember)->unk_09    = 0;
        SELF(PartyMember)->timer     = 1;
        SELF(PartyMember)->unk_04    = 16;
        SELF(PartyMember)->header.step += 1;
        SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
}

/* Stream step 1: lengthens the stream by 3 segments per frame for 8 frames, then sets task byte 0x0B to 1. */
/* func_801EF270 */
MATCH void BMagic_WhelpBreathStreamGrow(void) {
    u8 counter;
    SELF(PartyMember)->timer += 3;
    counter                   = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = counter;
    if ((counter & BYTE_MASK) == 8) {
        g_BattleEffectBattler->param.unk_0B = BMAGIC_WHELP_BREATH_GROWN;
        SELF(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_CountUpTimerCallSelector.h"

#include "overlays/bmagic/shared/Effect_CountUpAndStepAt120.h"

#include "overlays/bmagic/shared/Effect_CountUpAndFinishAt136.h"

/* Draws the stream as two bands of textured quads that sway along the stream's angle. */
/* func_801EF44C */
MATCH void BMagic_WhelpBreathDrawStream(void) {
    POLY_GT4* prim;
    s32       tpage;
    s32       i;
    s32       inner;
    s32       outer;
    s32       swing;
    s32       prev;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    g_ScratchPad.cells.halves[4] = SELF(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[5] = SELF(PartyMember)->screen_y.value;
    g_ScratchPad.cells.halves[1] = SELF(PartyMember)->unk_14;
    for (i = 1; i < SELF(PartyMember)->timer + 1; i++) {
        g_ScratchPad.cells.halves[6] = g_ScratchPad.cells.halves[4];
        g_ScratchPad.cells.halves[7] = g_ScratchPad.cells.halves[5];
        g_ScratchPad.cells.halves[2] = (g_ScratchPad.cells.halves[1] + FIXED_MUL(rsin(((i + SELF(PartyMember)->unk_09) << 6) & 0xFC0), 352)) & ANGLE_MASK;
        g_ScratchPad.cells.halves[4] += FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), 16);
        g_ScratchPad.cells.halves[5] += FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), 16);
        prim  = (POLY_GT4*)g_GfxPrimCursor;
        inner = ((i - 1 - SELF(PartyMember)->unk_09) & 0x3F) << 6;
        outer = ((i - SELF(PartyMember)->unk_09) & 0x3F) << 6;
        SetPolyGT4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPad.cells.halves[2] = (g_ScratchPad.cells.halves[1] + 0x400) & ANGLE_MASK;
        prev                         = i - 1;
        swing                        = rsin(inner) * 2;
        swing                        = FIXED_MUL(swing, prev) + 4;
        g_ScratchPad.cells.halves[0] = prev * 4 + swing;
        g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[0] / SELF(PartyMember)->param.unk_0B + 1;
        prim->x1                     = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y1                     = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        swing                        = rsin(outer) * 2;
        swing                        = FIXED_MUL(swing, i) + 4;
        g_ScratchPad.cells.halves[0] = i * 4 + swing;
        g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[0] / SELF(PartyMember)->param.unk_0B + 1;
        prim->x3                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y3                     = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        setXY0(prim, g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7]);
        prim->x2    = g_ScratchPad.cells.halves[4];
        prim->y2    = g_ScratchPad.cells.halves[5];
        prim->clut  = GetClut(0, 0x1FA);
        prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100);
        setUV4(prim, 0x40, i * 8 - SELF(PartyMember)->unk_09 * 16, 0x80, i * 8 - SELF(PartyMember)->unk_09 * 16, 0x40, i * 8 - SELF(PartyMember)->unk_09 * 16 + 8, 0x80,
               i * 8 - SELF(PartyMember)->unk_09 * 16 + 8);
        g_ScratchPad.cells.halves[3] = SELF(PartyMember)->unk_04 * 12;
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        g_ScratchPad.cells.halves[3] = SELF(PartyMember)->unk_04;
        setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB3(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_GT4));
        prim = (POLY_GT4*)g_GfxPrimCursor;
        SetPolyGT4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPad.cells.halves[2] = (g_ScratchPad.cells.halves[1] - 0x400) & ANGLE_MASK;
        swing                        = rsin(inner) * 2;
        swing                        = FIXED_MUL(swing, prev) + 4;
        g_ScratchPad.cells.halves[0] = prev * 4 + swing;
        g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[0] / SELF(PartyMember)->param.unk_0B + 1;
        setXY0(prim, g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]),
               g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]));
        swing                        = rsin(outer) * 2;
        swing                        = FIXED_MUL(swing, i) + 4;
        g_ScratchPad.cells.halves[0] = i * 4 + swing;
        g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[0] / SELF(PartyMember)->param.unk_0B + 1;
        prim->x2                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y2                     = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->x1                     = g_ScratchPad.cells.halves[6];
        prim->y1                     = g_ScratchPad.cells.halves[7];
        prim->x3                     = g_ScratchPad.cells.halves[4];
        prim->y3                     = g_ScratchPad.cells.halves[5];
        prim->clut                   = GetClut(0, 0x1FA);
        prim->tpage                  = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100);
        setUV4(prim, 0, i * 8 - SELF(PartyMember)->unk_09 * 16, 0x40, i * 8 - SELF(PartyMember)->unk_09 * 16, 0, i * 8 - SELF(PartyMember)->unk_09 * 16 + 8, 0x40,
               i * 8 - SELF(PartyMember)->unk_09 * 16 + 8);
        g_ScratchPad.cells.halves[3] = SELF(PartyMember)->unk_04 * 12;
        setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB3(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        g_ScratchPad.cells.halves[3] = SELF(PartyMember)->unk_04;
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_GT4));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, tpage);
}

#include "overlays/bmagic/shared/BMagic_RunStep.h"

/* Actor step 0: sets the actor up and, by its role, picks its script and its next step. */
/* func_801EFDD4 */
MATCH void BMagic_WhelpBreathActorStart(void) {
    PartyMember* work;
    u32          i;

    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&SELF(PartyMember)->pos, &g_BattleEffectBattler->pos);
    SELF(PartyMember)->unk_25 = 29;
    SELF(PartyMember)->unk_26 = 0;
    SELF(PartyMember)->unk_27 = 0xA1;
    SELF(PartyMember)->unk_28 = 0;
    SELF(PartyMember)->unk_2A = g_BattleEffectBattler->facing & 1;
    SELF(PartyMember)->unk_29 = 3;
    SELF(PartyMember)->unk_24 = 4;
    work                      = SELF(PartyMember);
    work->unk_2B              = 0;
    work->unk_2C.value        = 0;
    switch (SELF(PartyMember)->param.unk_0B) {
        case BMAGIC_WHELP_BREATH_ACTOR_PLAY:
            SELF(PartyMember)->header.step += 1;
            if (SELF(PartyMember)->facing & 2) {
                SELF(PartyMember)->unk_29 = 4;
                SELF(PartyMember)->unk_2A = ~SELF(PartyMember)->facing & 1;
                Script_Select(3);
            } else {
                Script_Select(0);
            }
            break;
        case BMAGIC_WHELP_BREATH_ACTOR_LOOP:
            SELF(PartyMember)->unk_09      = 120;
            SELF(PartyMember)->header.step = 2;
            Script_Select(1);
            break;
        case BMAGIC_WHELP_BREATH_ACTOR_PUFFS:
            for (i = 0; i < 6; i++) {
                g_BMagicWhelpBreathPuffAges[i] = 0;
            }
            SELF(PartyMember)->unk_09      = 0;
            SELF(PartyMember)->header.step = 3;
            break;
        case BMAGIC_WHELP_BREATH_ACTOR_SHADE:
            SELF(PartyMember)->unk_09      = 0;
            SELF(PartyMember)->timer       = 80;
            SELF(PartyMember)->header.step = 5;
            break;
    }
}

/* Actor step 1: draws the actor and plays its script once. */
/* func_801F0008 */
MATCH void BMagic_WhelpBreathActorPlay(void) {
    Area_AddGridActor();
    if (Script_AnimStepOnce() & BYTE_MASK) {
        Effect_Reset();
    }
}

/* Actor step 2: draws the actor and loops its script for 120 frames. */
/* func_801F0044 */
MATCH void BMagic_WhelpBreathActorLoop(void) {
    u8 count;

    Script_AnimStepLoop();
    Area_AddGridActor();
    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        Effect_Reset();
    }
}

/* Puffs step 3: draws the puffs, which wrap around, for 96 frames. */
/* func_801F009C */
MATCH void BMagic_WhelpBreathPuffsLoop(void) {
    u8 timer;

    BMagic_WhelpBreathDrawPuffRows();
    timer                     = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 96) {
        SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;
    }
}

/* Puffs step 4: draws the puffs, which age out, for 16 frames. */
/* func_801F0104 */
MATCH void BMagic_WhelpBreathPuffsEnd(void) {
    u8 count;

    BMagic_WhelpBreathDrawPuffRows();
    count                     = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 0x70) {
        Effect_Reset();
    }
}

/* Shade step 5: draws the shade, which brightens over 16 frames. */
/* func_801F0158 */
MATCH void BMagic_WhelpBreathShadeFadeIn(void) {
    u8 timer;

    BMagic_WhelpBreathDrawShade();
    timer                     = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 16) {
        SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;
    }
}

/* Shade step 6: draws the shade for the 80 frames the actor start sets. */
/* func_801F01C0 */
MATCH void BMagic_WhelpBreathShadeHold(void) {
    u8 count;

    BMagic_WhelpBreathDrawShade();
    count                    = SELF(PartyMember)->timer - 1;
    SELF(PartyMember)->timer = count;
    if (count == 0) {
        SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;
    }
}

/* Shade step 7: draws the shade, which dims over 16 frames. */
/* func_801F0224 */
MATCH void BMagic_WhelpBreathShadeFadeOut(void) {
    u8 count;

    BMagic_WhelpBreathDrawShade();
    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        Effect_Reset();
    }
}

/* Draws the puffs in three rows over each selectable enemy, then ages them. */
/* func_801F0274 */
MATCH void BMagic_WhelpBreathDrawPuffRows(void) {
    PartyMember* work;
    s32          tpage;
    u32          j;
    u32          i;
    u8           enemy;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 8; i++) {
            enemy = i;
            if (Battle_SlotIsBlocked((i + BATTLE_PARTY_CHARACTERS_COUNT) & BYTE_MASK) != 0) {
                continue;
            }
            SELF(PartyMember)->param.unk_0B = j;
            SELF(PartyMember)->timer        = enemy;
            work                            = SELF(PartyMember);
            work->unk_0C                    = g_BMagicWhelpBreathPuffOffsets[j].x;
            work->unk_10                    = g_BMagicWhelpBreathPuffOffsets[j].y;
            Effect_RotatePosition(work);
            SELF(PartyMember)->pos.x.fixed = g_BattleEnemyBattlers[i].pos.x.fixed + SELF(PartyMember)->unk_0C;
            SELF(PartyMember)->pos.y.fixed = g_BattleEnemyBattlers[i].pos.y.fixed + SELF(PartyMember)->unk_10;
            SELF(PartyMember)->pos.z.fixed = g_BattleEnemyBattlers[i].pos.z.fixed + g_BMagicWhelpBreathPuffOffsets[j].z;
            SELF(PartyMember)->facing      = g_BattleEnemyBattlers[i].unk_08;
            BMagic_WhelpBreathSetEnemyMatrix();
            BMagic_WhelpBreathDrawPuffs();
            PopMatrix();
        }
    }
    for (j = 0; j < 6; j++) {
        if (j * 3 < SELF(PartyMember)->unk_09) {
            g_BMagicWhelpBreathPuffAges[j]++;
        }
        if (SELF(PartyMember)->header.step == 3) {
            g_BMagicWhelpBreathPuffAges[j] &= 0xF;
        }
    }
}

/* Draws a textured quad for each of the six puffs that has started and has not aged out:
 * the quad widens and rises and its shade fades as the puff's age grows. */
/* func_801F04B0 */
MATCH void BMagic_WhelpBreathDrawPuffs(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       z;

    for (i = 0; i < 6; i++) {
        if (i * 3 < SELF(PartyMember)->unk_09 && g_BMagicWhelpBreathPuffAges[i] < 16) {
            prim = (POLY_FT4*)g_GfxPrimCursor;
            SetPolyFT4(prim);
            SetSemiTrans(prim, 1);
            g_ScratchPad.cells.halves[0] = g_BMagicWhelpBreathPuffAges[i] * 4 + 50;
            z                            = g_BMagicWhelpBreathPuffAges[i] * 15;
            g_ScratchPadVectors[0].vx    = FIXED_MUL(rcos(512), g_ScratchPad.cells.halves[0]);
            g_ScratchPadVectors[0].vy    = FIXED_MUL(rsin(512), g_ScratchPad.cells.halves[0]);
            g_ScratchPadVectors[0].vz    = z;
            setVector(&g_ScratchPadVectors[1], FIXED_MUL(rcos(1536), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(1536), g_ScratchPad.cells.halves[0]), z);
            setVector(&g_ScratchPadVectors[2], FIXED_MUL(rcos(3584), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(3584), g_ScratchPad.cells.halves[0]), z);
            setVector(&g_ScratchPadVectors[3], FIXED_MUL(rcos(2560), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(2560), g_ScratchPad.cells.halves[0]), z);
            prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
            prim->clut  = GetClut(32, 506);
            setUVWH(prim, 8, 64, 32, 32);
            g_ScratchPad.cells.halves[3] = 97 - g_BMagicWhelpBreathPuffAges[i] * 6;
            setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                          &depth, &flag);
            GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_FT4));
        }
    }
}

/* Pushes the matrix that turns the puffs to the enemy's facing. */
/* func_801F078C */
MATCH void BMagic_WhelpBreathSetEnemyMatrix(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vz = 0;
    rot.vy = 0;
    rot.vx = 0;
    switch (SELF(PartyMember)->facing) {
        case 0:
            rot.vy = 3072;
            break;
        case 1:
            rot.vx = 1024;
            break;
        case 2:
            rot.vy = 1024;
            break;
        case 3:
            rot.vx = 3072;
            break;
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(SELF(PartyMember));
}

/* Draws the shade over each selectable enemy. */
/* func_801F08AC */
MATCH void BMagic_WhelpBreathDrawShade(void) {
    PartyMember* work;
    u32          i;

    for (i = 0; i < 8; i++) {
        if (Battle_SlotIsBlocked((i + BATTLE_PARTY_CHARACTERS_COUNT) & BYTE_MASK) != 0) {
            continue;
        }
        work                                = SELF(PartyMember);
        work->facing                        = g_BattleEnemyBattlers[i].unk_08;
        SELF(PartyMember)->pos.x.fixed      = g_BattleEnemyBattlers[i].pos.x.fixed;
        SELF(PartyMember)->pos.y.fixed      = g_BattleEnemyBattlers[i].pos.y.fixed;
        COORD_INT(SELF(PartyMember)->pos.z) = FIELD(u16, D_801EB66E, i * BATTLE_ENEMY_STRIDE);
        BMAGIC_DRAW_IN_ACTOR_MATRIX(BMagic_WhelpBreathDrawShadeWedge);
    }
}

/* Draws the shade as a darkening wedge on the enemy's facing. */
/* func_801F0974 */
MATCH void BMagic_WhelpBreathDrawShadeWedge(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    u32      phase;
    s32      tpage;

    g_ScratchPad.cells.halves[0] = (g_FrameCount & 0x3F) + 0x100;
    tpage                        = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    prim = GFX_BeginPolyG3(1);
    setVector(&g_ScratchPadVectors[0], 0, 0, 0);
    phase = (g_BMagicWhelpBreathShadePhases[SELF(PartyMember)->facing] - 6) & BMAGIC_PHASE_MASK;
    setVector(&g_ScratchPadVectors[1], FIXED_MUL(rsin(BMAGIC_PHASE_ANGLE(phase)), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(BMAGIC_PHASE_ANGLE(phase)), g_ScratchPad.cells.halves[0]), 0);
    phase = (g_BMagicWhelpBreathShadePhases[SELF(PartyMember)->facing] + 6) & BMAGIC_PHASE_MASK;
    setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(BMAGIC_PHASE_ANGLE(phase)), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(BMAGIC_PHASE_ANGLE(phase)), g_ScratchPad.cells.halves[0]), 0);
    setRGB0(prim, SELF(PartyMember)->unk_09 * 10 + 1, SELF(PartyMember)->unk_09 * 10 + 1, SELF(PartyMember)->unk_09 * 10 + 1);
    setRGB1(prim, 1, 1, 1);
    setRGB2(prim, 1, 1, 1);
    RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
    GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"
