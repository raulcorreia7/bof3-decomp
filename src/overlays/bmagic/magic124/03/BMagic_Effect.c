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
    SYS_DISPATCH_BYTE(handlers.steps, BMAGIC_WORK->header.mode);
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
    BMAGIC_WORK->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&BMAGIC_WORK->pos, &g_BattleEffectBattler->pos);
    Battle_ProjectRange();
    func_800B0118();
    BMAGIC_WORK->screen_x.value += BMAGIC_WORK->unk_0C;
    BMAGIC_WORK->screen_y.value += BMAGIC_WORK->unk_10;
    BMAGIC_WORK->param.unk_0B = 0;
    BMAGIC_WORK->unk_09       = 8;
    BMAGIC_WORK->timer        = 16;
    BMAGIC_WORK->header.mode++;
    for (i = 0; i < 32; i++) {
        slot                                   = BMagic_AllocEffect() & BYTE_MASK;
        task                                   = g_Task;
        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[slot].unk_04       = i;
        BMAGIC_EFFECT_SLOTS[slot].unk_0B       = 0;
        BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = i * 4 + 1;
        BMAGIC_EFFECT_SLOTS[slot].target.party = task;
        BMAGIC_WORK->param.unk_0B++;
    }
    SND_SEQueueSelection(0x100);
}

#include "overlays/bmagic/shared/Effect_RequestTargetOnTimerZero.h"

MATCH void func_801EEFF0(void) {
    u8 timer_next;

    if (BMAGIC_WORK->param.unk_0B < 3U) {
        timer_next         = BMAGIC_WORK->timer - 1;
        BMAGIC_WORK->timer = timer_next;
        if (!(timer_next & BYTE_MASK)) {
            BMAGIC_WORK->header.mode += 1;
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
    blue = red = green = BMAGIC_WORK->timer * 15;
    radius             = (rand() & 3) | 0x20;
    do {
        poly = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(poly);
        SetSemiTrans(poly, 1);
        setXY3(poly, BMAGIC_WORK->screen_x.value, BMAGIC_WORK->screen_y.value, BMAGIC_WORK->screen_x.value + ((rsin(i << 9) * radius) >> 12),
               BMAGIC_WORK->screen_y.value + ((rcos(i << 9) * radius) >> 12), BMAGIC_WORK->screen_x.value + ((rsin((i + 1) << 9) * radius) >> 12),
               BMAGIC_WORK->screen_y.value + ((rcos((i + 1) << 9) * radius) >> 12));
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
    if (BMAGIC_WORK->header.flags != 0 && BMAGIC_WORK->header.step != 0) {
        BMAGIC_WORK->param.unk_0B++;
        func_801EF6E8();
        if ((BMAGIC_WORK->param.unk_0B & 3) == 0) {
            if (BMAGIC_WORK->header.step == 1) {
                if (BMAGIC_WORK->timer != 0) {
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

    if (--BMAGIC_WORK->unk_09 == 0) {
        Battle_CenterCamera();
        Battle_ProjectRange();
        battler                      = g_BattleEffectBattler;
        g_ScratchPad.cells.halves[6] = BMAGIC_WORK->screen_x.value;
        g_ScratchPad.cells.halves[7] = BMAGIC_WORK->screen_y.value;
        g_ScratchPad.cells.halves[4] = BMAGIC_WORK->screen_x.value = battler->screen_x.value;
        g_ScratchPad.cells.halves[5] = BMAGIC_WORK->screen_y.value = battler->screen_y.value;
        BMAGIC_WORK->unk_14                                        = ratan2(g_ScratchPad.cells.halves[6] - g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[7] - g_ScratchPad.cells.halves[5]);
        if (BMAGIC_WORK->unk_04 & 1) {
            BMAGIC_WORK->unk_14 += (rand() & 7) << 6;
        } else {
            BMAGIC_WORK->unk_14 -= (rand() & 7) << 6;
        }
        BMAGIC_WORK->unk_0C       = 0;
        BMAGIC_WORK->param.unk_0B = rand() & 0x3F;
        BMAGIC_WORK->unk_09       = 0x10;
        BMAGIC_WORK->timer        = 0;
        BMAGIC_WORK->header.step++;
    }
}

MATCH void func_801EF588(void) {
    u8 timer;

    BMAGIC_STEP_TIMER(timer, 4, 16);
}

MATCH void func_801EF5D8(void) {
    BMAGIC_WORK->timer = 16 + (rsin((BMAGIC_WORK->param.unk_0B & 0x3F) << 6) * 4 >> 12);
    BMAGIC_WORK->unk_0C++;
    if (BMAGIC_WORK->unk_0C == 0x10) {
        BMAGIC_WORK->header.step++;
    }
}

MATCH void func_801EF654(void) {
    u8 timer;

    BMAGIC_WORK->timer  = ((rsin((BMAGIC_WORK->param.unk_0B & 0x3F) << 6) * 4) >> 0xC) + 16;
    timer               = BMAGIC_WORK->unk_09 - 2;
    BMAGIC_WORK->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Actor_Clear();
    }
}

#ifdef NON_MATCHING
NON_MATCHING void func_801EF6E8(void) {
}
#else
INCLUDE_ASM(func_801EF6E8);
#endif

MATCH void func_801F020C(void) {
    SYS_DISPATCH_BYTE(D_801F08F4, BMAGIC_WORK->header.step);
    if (BMAGIC_WORK->header.flags != 0 && BMAGIC_WORK->header.step != 0) {
        func_801F03E0();
        func_801F05B4();
    }
}

MATCH void func_801F028C(void) {
    BMAGIC_WORK->unk_5D = 8;
    BMAGIC_WORK->unk_5E = 6;
    BMAGIC_WORK->unk_5F = 15;
    BMAGIC_WORK->unk_09 = 0;
    BMAGIC_WORK->timer  = 2;
    BMAGIC_WORK->header.step++;
}

MATCH void func_801F02FC(void) {
    PartyMember* work;

    work = g_Task;
    work->timer += 2;
    work = g_Task;
    work->unk_09 += 4;
    if (work->unk_09 == 16) {
        work = g_Task;
        work->header.step++;
    }
}

MATCH void func_801F0368(void) {
    PartyMember* work;
    u8           count;

    work = g_Task;
    work->timer++;
    work         = g_Task;
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

    red    = BMAGIC_WORK->unk_09 * (s8)BMAGIC_WORK->unk_5D;
    green  = BMAGIC_WORK->unk_09 * (s8)BMAGIC_WORK->unk_5E;
    i      = 0;
    centre = BMAGIC_WORK->unk_09 * 15;
    radius = BMAGIC_WORK->timer * 2;
    blue   = BMAGIC_WORK->unk_09 * (s8)BMAGIC_WORK->unk_5F;
    do {
        poly = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(poly);
        SetSemiTrans(poly, 1);
        setXY3(poly, BMAGIC_WORK->screen_x.value, BMAGIC_WORK->screen_y.value, BMAGIC_WORK->screen_x.value + ((rsin(i << 9) * radius) >> 12),
               BMAGIC_WORK->screen_y.value + ((rcos(i << 9) * radius) >> 12), BMAGIC_WORK->screen_x.value + ((rsin((i + 1) << 9) * radius) >> 12),
               BMAGIC_WORK->screen_y.value + ((rcos((i + 1) << 9) * radius) >> 12));
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

    red   = BMAGIC_WORK->unk_09 * (s8)BMAGIC_WORK->unk_5D;
    green = BMAGIC_WORK->unk_09 * (s8)BMAGIC_WORK->unk_5E;
    i     = 0;
    outer = BMAGIC_WORK->timer * 3;
    inner = BMAGIC_WORK->timer * 2;
    blue  = BMAGIC_WORK->unk_09 * (s8)BMAGIC_WORK->unk_5F;
    do {
        poly = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(poly);
        SetSemiTrans(poly, 1);
        setXY4(poly, BMAGIC_WORK->screen_x.value + ((rsin(i << 9) * outer) >> 12), BMAGIC_WORK->screen_y.value + ((rcos(i << 9) * outer) >> 12),
               BMAGIC_WORK->screen_x.value + ((rsin((i + 1) << 9) * outer) >> 12), BMAGIC_WORK->screen_y.value + ((rcos((i + 1) << 9) * outer) >> 12),
               BMAGIC_WORK->screen_x.value + ((rsin(i << 9) * inner) >> 12), BMAGIC_WORK->screen_y.value + ((rcos(i << 9) * inner) >> 12),
               BMAGIC_WORK->screen_x.value + ((rsin((i + 1) << 9) * inner) >> 12), BMAGIC_WORK->screen_y.value + ((rcos((i + 1) << 9) * inner) >> 12));
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
