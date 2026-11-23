#include "magic124_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC14(void) {
    Magic010Steps handlers;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    s32           tpage;
    u8            i;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.mode);
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    BMAGIC_RUN_EFFECT_SLOTS(BMAGIC_EFFECT_SLOTS, BMagic_DispatchEffectMode);
    func_801EF0B0();
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, tpage);
}

MATCH void func_801EEDD8(void) {
    PartyMember* task;
    u32          slot;
    u32          i;

    BMAGIC_CLEAR_EFFECTS(i);
    TASK(PartyMember)->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&TASK(PartyMember)->pos, &g_BattleEffectBattler->pos);
    Battle_ProjectRange();
    func_800B0118();
    TASK(PartyMember)->screen_x.value += TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->screen_y.value += TASK(PartyMember)->unk_10;
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 8;
    TASK(PartyMember)->timer        = 16;
    TASK(PartyMember)->header.mode++;
    for (i = 0; i < 32; i++) {
        slot                                   = BMagic_AllocEffect() & BYTE_MASK;
        task                                   = TASK(PartyMember);
        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[slot].unk_04       = i;
        BMAGIC_EFFECT_SLOTS[slot].unk_0B       = 0;
        BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = i * 4 + 1;
        BMAGIC_EFFECT_SLOTS[slot].target.party = task;
        TASK(PartyMember)->param.unk_0B++;
    }
    SND_SEQueueSelection(0x100);
}

#include "overlays/bmagic/shared/Effect_RequestTargetOnTimerZero.h"

MATCH void func_801EEFF0(void) {
    u8 timer_next;

    if (TASK(PartyMember)->param.unk_0B < 3U) {
        timer_next               = TASK(PartyMember)->timer - 1;
        TASK(PartyMember)->timer = timer_next;
        if (!(timer_next & BYTE_MASK)) {
            TASK(PartyMember)->header.mode += 1;
        }
    }
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

MATCH void func_801EF0B0(void) {
    POLY_G3* poly;
    s32      radius;
    u8       red;
    u8       green;
    u8       blue;
    u8       i;

    i    = 0;
    blue = red = green = TASK(PartyMember)->timer * 15;
    radius             = (rand() & 3) | 0x20;
    do {
        poly = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(poly);
        SetSemiTrans(poly, 1);
        setXY3(poly, TASK(PartyMember)->screen_x.value, TASK(PartyMember)->screen_y.value, TASK(PartyMember)->screen_x.value + ((rsin(i << 9) * radius) >> 12),
               TASK(PartyMember)->screen_y.value + ((rcos(i << 9) * radius) >> 12), TASK(PartyMember)->screen_x.value + ((rsin((i + 1) << 9) * radius) >> 12),
               TASK(PartyMember)->screen_y.value + ((rcos((i + 1) << 9) * radius) >> 12));
        setRGB0(poly, red, green, blue);
        setRGB1(poly, 1, 1, 1);
        setRGB2(poly, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G3));
        i++;
    } while (i < 8);
}

MATCH void func_801EF268(void) {
}

/* func_801EF270 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF2B4(void) {
    u8           slot;
    PartyMember* battler;

    SYS_DISPATCH_TASK(g_BMagicEffectModes + 2, 2, g_Task);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        TASK(PartyMember)->param.unk_0B++;
        func_801EF6E8();
        if ((TASK(PartyMember)->param.unk_0B & 3) == 0) {
            if (TASK(PartyMember)->header.step == 1) {
                if (TASK(PartyMember)->timer != 0) {
                    slot = BMagic_AllocEffect();
                    if (slot != 0xFF) {
                        battler                                = g_BattleEffectBattler;
                        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 1;
                        BMAGIC_EFFECT_SLOTS[slot].target.party = battler;
                        BMAGIC_EFFECT_SLOTS[slot].screen_x     = g_ScratchPad.cells.halves[4];
                        BMAGIC_EFFECT_SLOTS[slot].screen_y     = g_ScratchPad.cells.halves[5];
                        g_BattleEffectBattler->param.unk_0B++;
                    }
                }
            }
        }
    }
}

MATCH void func_801EF3FC(void) {
    PartyMember* battler;

    if (--TASK(PartyMember)->unk_09 == 0) {
        Battle_CenterCamera();
        Battle_ProjectRange();
        battler                      = g_BattleEffectBattler;
        g_ScratchPad.cells.halves[6] = TASK(PartyMember)->screen_x.value;
        g_ScratchPad.cells.halves[7] = TASK(PartyMember)->screen_y.value;
        g_ScratchPad.cells.halves[4] = TASK(PartyMember)->screen_x.value = battler->screen_x.value;
        g_ScratchPad.cells.halves[5] = TASK(PartyMember)->screen_y.value = battler->screen_y.value;
        TASK(PartyMember)->unk_14 = ratan2(g_ScratchPad.cells.halves[6] - g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[7] - g_ScratchPad.cells.halves[5]);
        if (TASK(PartyMember)->unk_04 & 1) {
            TASK(PartyMember)->unk_14 += (rand() & 7) << 6;
        } else {
            TASK(PartyMember)->unk_14 -= (rand() & 7) << 6;
        }
        TASK(PartyMember)->unk_0C       = 0;
        TASK(PartyMember)->param.unk_0B = rand() & 0x3F;
        TASK(PartyMember)->unk_09       = 0x10;
        TASK(PartyMember)->timer        = 0;
        TASK(PartyMember)->header.step++;
    }
}

MATCH void func_801EF588(void) {
    u8 timer;

    BMAGIC_STEP_TIMER(timer, 4, 16);
}

MATCH void func_801EF5D8(void) {
    TASK(PartyMember)->timer = 16 + (rsin((TASK(PartyMember)->param.unk_0B & 0x3F) << 6) * 4 >> 12);
    TASK(PartyMember)->unk_0C++;
    if (TASK(PartyMember)->unk_0C == 0x10) {
        TASK(PartyMember)->header.step++;
    }
}

MATCH void func_801EF654(void) {
    u8 timer;

    TASK(PartyMember)->timer  = ((rsin((TASK(PartyMember)->param.unk_0B & 0x3F) << 6) * 4) >> 0xC) + 16;
    timer                     = TASK(PartyMember)->unk_09 - 2;
    TASK(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Actor_Clear();
    }
}

/* Draws the magic124 ribbon: timer segments stepping from the effect position along unk_14, each a pair of semi-transparent Gouraud bands swung by a sine of the segment and unk_0B, fading to white at the tail. */
#define RIBBON_PREV_WIDTH g_ScratchPad.cells.halves[0]
#define RIBBON_WIDTH      g_ScratchPad.cells.halves[1]
#define RIBBON_NEXT_ANGLE g_ScratchPad.cells.halves[2]
#define RIBBON_PREV_ANGLE g_ScratchPad.cells.halves[3]
#define RIBBON_NEXT_X     g_ScratchPad.cells.halves[4]
#define RIBBON_NEXT_Y     g_ScratchPad.cells.halves[5]
#define RIBBON_PREV_X     g_ScratchPad.cells.halves[6]
#define RIBBON_PREV_Y     g_ScratchPad.cells.halves[7]

MATCH void func_801EF6E8(void) {
    POLY_G4* prim;
    s16      sway;
    u8       grey;
    u8       red;
    u8       green;
    u8       i;
    s16      angle;

    RIBBON_WIDTH              = (rand() & 1) + 3;
    red                       = TASK(PartyMember)->unk_09 * 8;
    green                     = TASK(PartyMember)->unk_09 * 4;
    grey                      = TASK(PartyMember)->unk_09 * 15;
    g_ScratchPadVectors[0].vx = RIBBON_PREV_X = TASK(PartyMember)->screen_x.value;
    g_ScratchPadVectors[0].vy = RIBBON_PREV_Y = TASK(PartyMember)->screen_y.value;
    angle                                     = TASK(PartyMember)->unk_14 - 0x400;
    sway                                      = FIXED_MUL(rsin((TASK(PartyMember)->param.unk_0B & 0x1F) << 7), 4);
    RIBBON_NEXT_X                             = g_ScratchPadVectors[0].vx + FIXED_MUL(rsin(angle), sway);
    RIBBON_NEXT_Y                             = g_ScratchPadVectors[0].vy + FIXED_MUL(rcos(angle), sway);
    RIBBON_NEXT_ANGLE                         = ratan2(RIBBON_PREV_X - RIBBON_NEXT_X, RIBBON_PREV_Y - RIBBON_NEXT_Y) - 0x400;
    for (i = 1; i < TASK(PartyMember)->timer + 1; i++) {
        RIBBON_PREV_WIDTH = RIBBON_WIDTH;
        if ((i & 7) == 0) {
            RIBBON_WIDTH = (rand() & 3) + 2;
        }
        RIBBON_PREV_X = RIBBON_NEXT_X;
        RIBBON_PREV_Y = RIBBON_NEXT_Y;
        g_ScratchPadVectors[0].vx += FIXED_MUL(rsin(TASK(PartyMember)->unk_14), 16);
        g_ScratchPadVectors[0].vy += FIXED_MUL(rcos(TASK(PartyMember)->unk_14), 16);
        sway              = FIXED_MUL(rsin(((TASK(PartyMember)->param.unk_0B + i) & 0x1F) << 7), FIXED_MUL(rsin(i * (0x800 / TASK(PartyMember)->timer)), (rand() & 0xF) + 0x18));
        RIBBON_NEXT_X     = g_ScratchPadVectors[0].vx + FIXED_MUL(rsin(angle), sway);
        RIBBON_NEXT_Y     = g_ScratchPadVectors[0].vy + FIXED_MUL(rcos(angle), sway);
        RIBBON_PREV_ANGLE = RIBBON_NEXT_ANGLE + 0x400;
        RIBBON_NEXT_ANGLE = ratan2(RIBBON_PREV_X - RIBBON_NEXT_X, RIBBON_PREV_Y - RIBBON_NEXT_Y);
        prim              = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        RIBBON_PREV_ANGLE += 0x400;
        RIBBON_NEXT_ANGLE += 0x400;
        prim->x1 = RIBBON_PREV_X + FIXED_MUL(rsin(RIBBON_PREV_ANGLE), RIBBON_PREV_WIDTH);
        prim->y1 = RIBBON_PREV_Y + FIXED_MUL(rcos(RIBBON_PREV_ANGLE), RIBBON_PREV_WIDTH);
        prim->x3 = RIBBON_NEXT_X + FIXED_MUL(rsin(RIBBON_NEXT_ANGLE), RIBBON_WIDTH);
        prim->y3 = RIBBON_NEXT_Y + FIXED_MUL(rcos(RIBBON_NEXT_ANGLE), RIBBON_WIDTH);
        prim->x0 = RIBBON_PREV_X;
        prim->y0 = RIBBON_PREV_Y;
        prim->x2 = RIBBON_NEXT_X;
        prim->y2 = RIBBON_NEXT_Y;
        setRGB0(prim, grey, grey, grey);
        setRGB2(prim, grey, grey, grey);
        setRGB1(prim, red, green, grey);
        setRGB3(prim, red, green, grey);
        if (TASK(PartyMember)->timer == i) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));

        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        prim->x1 = RIBBON_PREV_X + FIXED_MUL(rsin(RIBBON_PREV_ANGLE), RIBBON_PREV_WIDTH + 8);
        prim->y1 = RIBBON_PREV_Y + FIXED_MUL(rcos(RIBBON_PREV_ANGLE), RIBBON_PREV_WIDTH + 8);
        prim->x3 = RIBBON_NEXT_X + FIXED_MUL(rsin(RIBBON_NEXT_ANGLE), RIBBON_WIDTH + 8);
        prim->y3 = RIBBON_NEXT_Y + FIXED_MUL(rcos(RIBBON_NEXT_ANGLE), RIBBON_WIDTH + 8);
        prim->x0 = RIBBON_PREV_X + FIXED_MUL(rsin(RIBBON_PREV_ANGLE), RIBBON_PREV_WIDTH);
        prim->y0 = RIBBON_PREV_Y + FIXED_MUL(rcos(RIBBON_PREV_ANGLE), RIBBON_PREV_WIDTH);
        prim->x2 = RIBBON_NEXT_X + FIXED_MUL(rsin(RIBBON_NEXT_ANGLE), RIBBON_WIDTH);
        prim->y2 = RIBBON_NEXT_Y + FIXED_MUL(rcos(RIBBON_NEXT_ANGLE), RIBBON_WIDTH);
        setRGB0(prim, red, green, grey);
        setRGB2(prim, red, green, grey);
        setRGB1(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        if (TASK(PartyMember)->timer == i) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));

        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        RIBBON_PREV_ANGLE -= 0x800;
        RIBBON_NEXT_ANGLE -= 0x800;
        prim->x0 = RIBBON_PREV_X + FIXED_MUL(rsin(RIBBON_PREV_ANGLE), RIBBON_PREV_WIDTH);
        prim->y0 = RIBBON_PREV_Y + FIXED_MUL(rcos(RIBBON_PREV_ANGLE), RIBBON_PREV_WIDTH);
        prim->x2 = RIBBON_NEXT_X + FIXED_MUL(rsin(RIBBON_NEXT_ANGLE), RIBBON_WIDTH);
        prim->y2 = RIBBON_NEXT_Y + FIXED_MUL(rcos(RIBBON_NEXT_ANGLE), RIBBON_WIDTH);
        prim->x1 = RIBBON_PREV_X;
        prim->y1 = RIBBON_PREV_Y;
        prim->x3 = RIBBON_NEXT_X;
        prim->y3 = RIBBON_NEXT_Y;
        setRGB1(prim, grey, grey, grey);
        setRGB3(prim, grey, grey, grey);
        setRGB0(prim, red, green, grey);
        setRGB2(prim, red, green, grey);
        if (TASK(PartyMember)->timer == i) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));

        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        prim->x0 = RIBBON_PREV_X + FIXED_MUL(rsin(RIBBON_PREV_ANGLE), RIBBON_PREV_WIDTH + 8);
        prim->y0 = RIBBON_PREV_Y + FIXED_MUL(rcos(RIBBON_PREV_ANGLE), RIBBON_PREV_WIDTH + 8);
        prim->x2 = RIBBON_NEXT_X + FIXED_MUL(rsin(RIBBON_NEXT_ANGLE), RIBBON_WIDTH + 8);
        prim->y2 = RIBBON_NEXT_Y + FIXED_MUL(rcos(RIBBON_NEXT_ANGLE), RIBBON_WIDTH + 8);
        prim->x1 = RIBBON_PREV_X + FIXED_MUL(rsin(RIBBON_PREV_ANGLE), RIBBON_PREV_WIDTH);
        prim->y1 = RIBBON_PREV_Y + FIXED_MUL(rcos(RIBBON_PREV_ANGLE), RIBBON_PREV_WIDTH);
        prim->x3 = RIBBON_NEXT_X + FIXED_MUL(rsin(RIBBON_NEXT_ANGLE), RIBBON_WIDTH);
        prim->y3 = RIBBON_NEXT_Y + FIXED_MUL(rcos(RIBBON_NEXT_ANGLE), RIBBON_WIDTH);
        setRGB1(prim, red, green, grey);
        setRGB3(prim, red, green, grey);
        setRGB0(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        if (TASK(PartyMember)->timer == i) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
    }
}

MATCH void func_801F020C(void) {
    SYS_DISPATCH_BYTE(D_801F08F4, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        func_801F03E0();
        func_801F05B4();
    }
}

MATCH void func_801F028C(void) {
    TASK(PartyMember)->unk_5D = 8;
    TASK(PartyMember)->unk_5E = 6;
    TASK(PartyMember)->unk_5F = 15;
    TASK(PartyMember)->unk_09 = 0;
    TASK(PartyMember)->timer  = 2;
    TASK(PartyMember)->header.step++;
}

MATCH void func_801F02FC(void) {
    PartyMember* work;

    work = TASK(PartyMember);
    work->timer += 2;
    work = TASK(PartyMember);
    work->unk_09 += 4;
    if (work->unk_09 == 16) {
        work = TASK(PartyMember);
        work->header.step++;
    }
}

MATCH void func_801F0368(void) {
    PartyMember* work;
    u8           count;

    work = TASK(PartyMember);
    work->timer++;
    work         = TASK(PartyMember);
    count        = work->unk_09 - 4;
    work->unk_09 = count;
    if (count == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B--;
        Actor_Clear();
    }
}

MATCH void func_801F03E0(void) {
    POLY_G3* poly;
    s32      radius;
    u8       red;
    u8       green;
    u8       blue;
    u8       centre;
    u8       i;

    red    = TASK(PartyMember)->unk_09 * (s8)TASK(PartyMember)->unk_5D;
    green  = TASK(PartyMember)->unk_09 * (s8)TASK(PartyMember)->unk_5E;
    i      = 0;
    centre = TASK(PartyMember)->unk_09 * 15;
    radius = TASK(PartyMember)->timer * 2;
    blue   = TASK(PartyMember)->unk_09 * (s8)TASK(PartyMember)->unk_5F;
    do {
        poly = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(poly);
        SetSemiTrans(poly, 1);
        setXY3(poly, TASK(PartyMember)->screen_x.value, TASK(PartyMember)->screen_y.value, TASK(PartyMember)->screen_x.value + ((rsin(i << 9) * radius) >> 12),
               TASK(PartyMember)->screen_y.value + ((rcos(i << 9) * radius) >> 12), TASK(PartyMember)->screen_x.value + ((rsin((i + 1) << 9) * radius) >> 12),
               TASK(PartyMember)->screen_y.value + ((rcos((i + 1) << 9) * radius) >> 12));
        setRGB0(poly, centre, centre, centre);
        setRGB1(poly, red, green, blue);
        setRGB2(poly, red, green, blue);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G3));
        i++;
    } while (i < 8);
}

MATCH void func_801F05B4(void) {
    POLY_G4* poly;
    s32      outer;
    s32      inner;
    u8       red;
    u8       green;
    u8       blue;
    u8       i;

    red   = TASK(PartyMember)->unk_09 * (s8)TASK(PartyMember)->unk_5D;
    green = TASK(PartyMember)->unk_09 * (s8)TASK(PartyMember)->unk_5E;
    i     = 0;
    outer = TASK(PartyMember)->timer * 3;
    inner = TASK(PartyMember)->timer * 2;
    blue  = TASK(PartyMember)->unk_09 * (s8)TASK(PartyMember)->unk_5F;
    do {
        poly = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(poly);
        SetSemiTrans(poly, 1);
        setXY4(poly, TASK(PartyMember)->screen_x.value + ((rsin(i << 9) * outer) >> 12), TASK(PartyMember)->screen_y.value + ((rcos(i << 9) * outer) >> 12),
               TASK(PartyMember)->screen_x.value + ((rsin((i + 1) << 9) * outer) >> 12), TASK(PartyMember)->screen_y.value + ((rcos((i + 1) << 9) * outer) >> 12),
               TASK(PartyMember)->screen_x.value + ((rsin(i << 9) * inner) >> 12), TASK(PartyMember)->screen_y.value + ((rcos(i << 9) * inner) >> 12),
               TASK(PartyMember)->screen_x.value + ((rsin((i + 1) << 9) * inner) >> 12), TASK(PartyMember)->screen_y.value + ((rcos((i + 1) << 9) * inner) >> 12));
        setRGB0(poly, 1, 1, 1);
        setRGB1(poly, 1, 1, 1);
        setRGB2(poly, red, green, blue);
        setRGB3(poly, red, green, blue);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
        i++;
    } while (i < 8);
}

/* func_801F0828 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

/* func_801F088C */
#include "overlays/bmagic/shared/Actor_Clear.h"
