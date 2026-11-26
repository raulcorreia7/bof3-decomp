#include "magic123_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    s32          tpage;
    u8           i;

    BMagic_DispatchTaskPair(func_801EEDAC, Effect_MarkDamagedOnZeroTick);
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);

    BMAGIC_RUN_EFFECT_SLOTS(BMAGIC_EFFECT_SLOTS, BMagic_DispatchEffectMode);

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
}

MATCH void func_801EEDAC(void) {
    PartyMember* owner;
    u32          i;
    u8           slot;

    BMAGIC_CLEAR_EFFECTS(i);
    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    Battle_CenterCamera();
    Battle_ProjectRange();
    g_ScratchPad.cells.halves[5]   = SELF(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[6]   = SELF(PartyMember)->screen_y.value;
    SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    SELF(PartyMember)->pos.z       = g_BattleEffectBattler->pos.z;
    Battle_ProjectRange();
    if (g_Battle.active_battler < 3) {
        func_800B0118();
    } else {
        switch (SELF(PartyMember)->facing) {
            case 0:
                SELF(PartyMember)->unk_0C = 0x29;
                SELF(PartyMember)->unk_10 = -0xD;
                break;
            case 1:
                SELF(PartyMember)->unk_0C = -0x29;
                SELF(PartyMember)->unk_10 = -0xD;
                break;
            case 2:
                SELF(PartyMember)->unk_0C = -0x26;
                SELF(PartyMember)->unk_10 = -0x26;
                break;
            default:
                SELF(PartyMember)->unk_0C = 0x26;
                SELF(PartyMember)->unk_10 = -0x26;
                break;
        }
    }
    SELF(PartyMember)->screen_x.value += SELF(PartyMember)->unk_0C;
    SELF(PartyMember)->screen_y.value += SELF(PartyMember)->unk_10;
    g_ScratchPad.cells.halves[3]    = SELF(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[4]    = SELF(PartyMember)->screen_y.value;
    SELF(PartyMember)->unk_14       = ratan2(g_ScratchPad.cells.halves[5] - g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[6] - g_ScratchPad.cells.halves[4]);
    SELF(PartyMember)->param.unk_0B = 0;
    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        slot                                   = BMagic_AllocEffect();
        owner                                  = SELF(PartyMember);
        BMAGIC_EFFECT_SLOTS[slot].header.mode  = i & 1;
        BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = (i >> 2) * 3 + 1;
        BMAGIC_EFFECT_SLOTS[slot].target.party = owner;
        SELF(PartyMember)->param.unk_0B++;
    }
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x02));
    Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
    SELF(PartyMember)->unk_09 = 0;
    SELF(PartyMember)->header.mode++;
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EF0C4 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF108(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 2), 2, g_Self);
}

MATCH void func_801EF14C(void) {
    u8 timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        SELF(PartyMember)->screen_x.value = g_BattleEffectBattler->screen_x.value;
        SELF(PartyMember)->screen_y.value = g_BattleEffectBattler->screen_y.value;
        if RANDOM_MASK (1) {
            SELF(PartyMember)->unk_14 = g_BattleEffectBattler->unk_14 + RANDOM_MASK(BYTE_MASK);
        } else {
            SELF(PartyMember)->unk_14 = g_BattleEffectBattler->unk_14 - RANDOM_MASK(BYTE_MASK);
        }
        SELF(PartyMember)->unk_03       = RANDOM_MASK(7);
        SELF(PartyMember)->unk_0C       = RANDOM_MASK(7) + 8;
        SELF(PartyMember)->param.unk_0B = rand();
        SELF(PartyMember)->unk_09       = RANDOM_MASK(0xF) + 8;
        SELF(PartyMember)->timer        = 2;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF28C(void) {
    s16* angle;

    SELF(PartyMember)->param.unk_0B++;
    angle                        = &g_ScratchPad.cells.halves[2];
    *angle                       = SELF(PartyMember)->unk_14 + ((rsin((SELF(PartyMember)->param.unk_0B & 0x3F) << 6) * 128) >> 12);
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_0C;
    SELF(PartyMember)->screen_x.value += FIXED_MUL(rsin(*angle), g_ScratchPad.cells.halves[0]);
    SELF(PartyMember)->screen_y.value += FIXED_MUL(rcos(*angle), g_ScratchPad.cells.halves[0]);
    g_ScratchPad.cells.halves[3] = SELF(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[4] = SELF(PartyMember)->screen_y.value;
    if (SELF(PartyMember)->timer < SELF(PartyMember)->unk_03 + 6) {
        SELF(PartyMember)->timer += 2;
    }
    if (--SELF(PartyMember)->unk_09 == 0) {
        if (g_FrameCount & 1) {
            if (SELF(PartyMember)->header.mode & 1) {
                SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x00));
            } else {
                SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x01));
            }
        }
        SELF(PartyMember)->param.unk_0B = 0;
        SELF(PartyMember)->header.step++;
    }
    if (SELF(PartyMember)->screen_x.signed_value < 320 && SELF(PartyMember)->screen_y.signed_value < 240 && SELF(PartyMember)->screen_x.signed_value > 0 &&
        SELF(PartyMember)->screen_y.signed_value > 0) {
        func_801EF584();
        func_801EF750();
    }
}

MATCH void func_801EF4AC(void) {
    u8 timer;

    SELF(PartyMember)->param.unk_0B += 1;
    SELF(PartyMember)->unk_09 += 1;
    timer                    = SELF(PartyMember)->timer - 1;
    SELF(PartyMember)->timer = timer;
    if (!(timer & BYTE_MASK)) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        Actor_Clear();
        return;
    }
    func_801EF9E0();
}

/* func_801EF550 */
MATCH void Effect_ClearEffect(void) {
    BATTLE_ACTIVE_WORK->param.unk_0B--;
    Actor_Clear();
}

MATCH void func_801EF584(void) {
    POLY_G3* prim;
    s32      i;
    u8       phase;

    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->timer;
    for (i = 0; i < 6; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4]);
        phase                        = (D_801EFD6C[i] + SELF(PartyMember)->unk_09) & 0x3F;
        g_ScratchPad.cells.halves[2] = phase << 6;
        prim->x1                     = g_ScratchPad.cells.halves[3] + FIXED_MUL(rsin(phase << 6), g_ScratchPad.cells.halves[0]);
        prim->y1                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        phase                        = (D_801EFD6C[i + 1] + SELF(PartyMember)->unk_09) & 0x3F;
        g_ScratchPad.cells.halves[2] = phase << 6;
        prim->x2                     = g_ScratchPad.cells.halves[3] + FIXED_MUL(rsin(phase << 6), g_ScratchPad.cells.halves[0]);
        prim->y2                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        setRGB0(prim, 1, 1, 0xC0);
        setRGB1(prim, 0xE0, 0xE0, 0xE0);
        setRGB2(prim, 0xE0, 0xE0, 0xE0);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G3));
    }
}

/* Draws the six-quad ring arc around the effect position, blue at the inner rim and fading outward. */
MATCH void func_801EF750(void) {
    POLY_G4* prim;
    s32      i;
    u16      phase;

    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->timer;
    g_ScratchPad.cells.halves[7] = (SELF(PartyMember)->timer << 1) + (rand() & 7);
    for (i = 0; i < 6; i++) {
        prim = GFX_CURSOR(POLY_G4);
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        phase                        = (D_801EFD6C[i] + SELF(PartyMember)->unk_09) & 0x3F;
        g_ScratchPad.cells.halves[2] = phase << 6;
        setXY0(prim, g_ScratchPad.cells.halves[3] + FIXED_MUL(rsin(phase << 6), g_ScratchPad.cells.halves[7]),
               g_ScratchPad.cells.halves[4] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[7]));
        prim->x2                     = g_ScratchPad.cells.halves[3] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y2                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        phase                        = (D_801EFD6C[i + 1] + SELF(PartyMember)->unk_09) & 0x3F;
        g_ScratchPad.cells.halves[2] = phase << 6;
        prim->x1                     = g_ScratchPad.cells.halves[3] + FIXED_MUL(rsin(phase << 6), g_ScratchPad.cells.halves[7]);
        prim->y1                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[7]);
        prim->x3                     = g_ScratchPad.cells.halves[3] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y3                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 0x20, 0x20, 0xC0);
        setRGB3(prim, 0x20, 0x20, 0xC0);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
    }
}

/* Draws the eight-spark fan around the task screen position, turned by the step timer. */
MATCH void func_801EF9E0(void) {
    POLY_G3* prim;
    s16*     params;
    s32      angle;
    s32      i;
    s32      phase;
    s32      k;
    u8       shade;

    i                            = 0;
    g_ScratchPad.cells.halves[0] = (SELF(PartyMember)->param.unk_0B << 1) + 4;
    g_ScratchPad.cells.halves[7] = SELF(PartyMember)->timer;
    params                       = g_ScratchPad.cells.halves;
    shade                        = 0x20;
draw:
    phase     = i << 9;
    params[0] = (SELF(PartyMember)->param.unk_0B << 1) + 4 + (rand() & 3);
    params[3] = SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin(phase), params[0]);
    params[4] = SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos(phase), params[0]);

    prim = GFX_CURSOR(POLY_G3);
    SetPolyG3(prim);
    SetSemiTrans(prim, 1);

    k         = i * 2;
    angle     = (k + SELF(PartyMember)->unk_09) & 0xF;
    params[2] = angle << 8;
    setXY0(prim, params[3] + FIXED_MUL(rsin(params[2]), params[7]), params[4] + FIXED_MUL(rcos(params[2]), params[7]));

    angle     = (k + 5 + SELF(PartyMember)->unk_09) & 0xF;
    params[2] = angle << 8;
    prim->x1  = params[3] + FIXED_MUL(rsin(params[2]), params[7]);
    prim->y1  = params[4] + FIXED_MUL(rcos(params[2]), params[7]);

    k         = (k + 10 + SELF(PartyMember)->unk_09) & 0xF;
    params[2] = k << 8;
    prim->x2  = params[3] + FIXED_MUL(rsin(params[2]), params[7]);
    prim->y2  = params[4] + FIXED_MUL(rcos(params[2]), params[7]);

    setRGB0(prim, shade, shade, 0xC0);
    setRGB1(prim, 0xC0, 0xC0, 0xC0);
    setRGB2(prim, shade, shade, 0xC0);
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G3));
    i++;
    if (i < 8) {
        goto draw;
    }
}

/* func_801EFCA0 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

/* func_801EFD04 */
#include "overlays/bmagic/shared/Actor_Clear.h"
