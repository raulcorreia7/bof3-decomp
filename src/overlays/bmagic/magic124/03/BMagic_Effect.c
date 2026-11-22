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

#ifdef NON_MATCHING
NON_MATCHING void func_801EF6E8(void) {
}
#else
INCLUDE_ASM(func_801EF6E8);
#endif

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
