#include "magic219_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC14(void) {
    Magic219Steps handlers = D_801EEC04;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.mode);

    BMAGIC_RUN_EFFECT_SLOTS(D_801EFA14, BMagic_DispatchEffectMode);
}

/* Clears the effect slots, centers the camera and reloads palette rows 2 and 26 of the work copy with the STP bit
 * set. */
MATCH void func_801EED28(void) {
    u16* dst;
    u16* src;
    u16* row_dst;
    u16* row_src;
    u16  i;

    BMAGIC_CLEAR_EFFECTS(i);
    Battle_CenterCamera();
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->header.mode += 1;
    i       = 0;
    row_dst = g_AreaPaletteCopy->rows[AREA_PALETTE_BMAGIC_ROW].colors;
    row_src = g_AreaPaletteArena->rows[AREA_PALETTE_BMAGIC_ROW].colors;
    dst     = g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    src     = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    for (; i < AREA_PALETTE_COLORS; i++) {
        row_dst[i] = row_src[i] | PSX_COLOR_STP_BIT;
        dst[i]     = src[i] | PSX_COLOR_STP_BIT;
    }
    g_AreaPaletteCopy->rows[AREA_PALETTE_BMAGIC_ROW].colors[0]   = g_AreaPaletteArena->rows[AREA_PALETTE_BMAGIC_ROW].colors[0];
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0] = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0];
    g_GfxPalettePending                                          = 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
}

MATCH void func_801EEE50(void) {
    u8 i;
    u8 slot;

    for (i = 0; i < 24; i++) {
        slot = BMagic_AllocEffect();
        if (slot != GAME_NONE) {
            volatile void* task           = g_Self;
            D_801EFA14[slot].header.mode  = 0;
            D_801EFA14[slot].unk_0B       = i;
            D_801EFA14[slot].target.party = (PartyMember*)task;
            D_801EFA14[slot].arg.unk_09   = D_801EF9E8[i] + (RANDOM_MASK(0x1)) + 1;
            SELF(PartyMember)->param.unk_0B++;
        }
    }
    SELF(PartyMember)->unk_09 = 8;
    SELF(PartyMember)->header.mode++;
}

MATCH void func_801EEF54(void) {
    u8 timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        SND_SEQueueSelection(0x101);
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        SELF(PartyMember)->header.mode = SELF(PartyMember)->header.mode + 1;
    }
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EF024 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF068(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EFA04, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Area_AddGridActor();
        Effect_SetActiveActorMatrix();
        func_801EF71C();
        PopMatrix();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF118(void) {
    PartyMember* cell;
    u8           timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        cell                      = g_BattleActiveActor;
        SELF(PartyMember)->facing = cell->facing;
        SELF(PartyMember)->unk_0C = 0x20000;
        SELF(PartyMember)->unk_10 = 0;
        Effect_RotatePosition(g_Self);
        SELF(PartyMember)->pos.x.fixed  = cell->pos.x.fixed + SELF(PartyMember)->unk_0C;
        SELF(PartyMember)->pos.y.fixed  = cell->pos.y.fixed + SELF(PartyMember)->unk_10;
        SELF(PartyMember)->pos.z.fixed  = cell->pos.z.fixed + 0x800000;
        MAGIC219_RING_RADIUS            = (SELF(PartyMember)->param.unk_0B >> 3) * 16 + 32;
        MAGIC219_ORBIT_ANGLE            = (((SELF(PartyMember)->param.unk_0B & 7) * 2 + (SELF(PartyMember)->param.unk_0B >> 3)) & 0xF) << 8;
        SELF(PartyMember)->unk_0C       = g_BattleEffectBattler->pos.x.fixed + rsin(MAGIC219_ORBIT_ANGLE) * MAGIC219_RING_RADIUS;
        SELF(PartyMember)->unk_10       = g_BattleEffectBattler->pos.y.fixed + rcos(MAGIC219_ORBIT_ANGLE) * MAGIC219_RING_RADIUS;
        SELF(PartyMember)->unk_14       = g_BattleEffectBattler->pos.z.fixed;
        SELF(PartyMember)->unk_25       = 29;
        SELF(PartyMember)->unk_26       = 0xC0;
        SELF(PartyMember)->scale.x      = 0x10000;
        SELF(PartyMember)->scale.y      = 0x10000;
        SELF(PartyMember)->unk_48       = 0;
        SELF(PartyMember)->unk_27       = 2;
        SELF(PartyMember)->unk_28       = 1;
        SELF(PartyMember)->unk_24       = 0;
        SELF(PartyMember)->unk_5C       = 0;
        SELF(PartyMember)->unk_5D       = 0;
        SELF(PartyMember)->unk_5E       = 0;
        SELF(PartyMember)->unk_5F       = 0;
        SELF(PartyMember)->unk_2A       = 0;
        SELF(PartyMember)->unk_29       = 4;
        SELF(PartyMember)->unk_2C.value = 0;
        SELF(PartyMember)->unk_2B       = 0;
        Script_Select(0);
        SELF(PartyMember)->unk_18 = ratan2(SELF(PartyMember)->unk_0C - SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->unk_10 - SELF(PartyMember)->pos.y.fixed);
        SELF(PartyMember)->unk_09 = 3;
        SELF(PartyMember)->timer  = 4;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF3CC(void) {
    s32 vec[4];
    s32 x;
    s32 y;
    s32 z;
    s32 diff;
    u8  count;

    count = SELF(PartyMember)->unk_09;
    if (count != 0) {
        SELF(PartyMember)->unk_09 = count - 1;
        Script_AnimStepLoop();
    }
    x                         = SELF(PartyMember)->unk_0C;
    y                         = SELF(PartyMember)->unk_10;
    z                         = SELF(PartyMember)->unk_14;
    vec[0]                    = (x >> 9) - AREA_CELL_ORIGIN;
    vec[1]                    = (y >> 9) - AREA_CELL_ORIGIN;
    vec[2]                    = ((z >> 16) + 0xC0) >> 1;
    SELF(PartyMember)->unk_1C = SELF(PartyMember)->unk_18;
    SELF(PartyMember)->unk_18 = ratan2(x - SELF(PartyMember)->pos.x.fixed, y - SELF(PartyMember)->pos.y.fixed);
    Battle_StepRangeToward(vec[0], vec[1], vec[2], vec[3], 0x40);
    if (func_800AF720(x, y, 0x8000) != 0) {
        SELF(PartyMember)->header.step += 1;
    } else {
        diff                      = (SELF(PartyMember)->unk_1C & ANGLE_MASK) - (SELF(PartyMember)->unk_18 & ANGLE_MASK);
        SELF(PartyMember)->unk_1C = diff;
        if (diff < 0) {
            SELF(PartyMember)->unk_1C = ~diff + 1;
        }
        if ((u32)(SELF(PartyMember)->unk_1C - 0x601) < 0x3FF) {
            SELF(PartyMember)->header.step += 1;
        }
    }
}

MATCH void func_801EF530(void) {
    PartyMember* work = SELF(PartyMember);

    work->unk_25              = 0x1D;
    work->pos.x.fixed         = work->unk_0C;
    work->pos.y.fixed         = work->unk_10;
    work->pos.z.fixed         = work->unk_14;
    SELF(PartyMember)->unk_26 = 0;
    SELF(PartyMember)->unk_27 = 0x1A;
    SELF(PartyMember)->unk_2B = 1;
    Script_Select(1);
    SELF(PartyMember)->unk_09 = 0xE;
    SELF(PartyMember)->timer  = 12;
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801EF5DC(void) {
    u8 timer_next;
    u8 count;

    Script_AnimStepOnce();
    timer_next = SELF(PartyMember)->timer;
    if (timer_next != 0) {
        SELF(PartyMember)->timer = timer_next - 1;
    }
    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Actor_Clear();
    }
}

#include "overlays/bmagic/shared/Effect_SetActiveActorMatrix.h"

MATCH void func_801EF71C(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    MAGIC219_RING_RADIUS = SELF(PartyMember)->timer << 4;
    setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(0), MAGIC219_RING_RADIUS), FIXED_MUL(rcos(0), MAGIC219_RING_RADIUS), 0);
    g_ScratchPadVectors[1].vz = 0;
    g_ScratchPadVectors[0].vz = 0;
    for (i = 1; i <= 16; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        GFX_STEP_TRIANGLE_FAN(i << 8, MAGIC219_RING_RADIUS);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, 0x60, 0x60, 0x60);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }
}

/* func_801EF934 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

/* func_801EF998 */
#include "overlays/bmagic/shared/Actor_Clear.h"
