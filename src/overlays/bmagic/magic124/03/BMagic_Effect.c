#include "magic124_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC14(void) {
    Magic010SharedSteps handlers;
    PartyMember*        saved_task;
    PartyMember*        saved_battler;
    s32                 tpage;
    u8                  i;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);
    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0xA5 : 0x35;
    GFX_AddDitheredDrawMode(3, tpage);
    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (BMAGIC_EFFECT_SLOTS[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&BMAGIC_EFFECT_SLOTS[i];
            g_BattleEffectBattler = BMAGIC_EFFECT_SLOTS[i].target.party;
            BMagic_DispatchEffectMode();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
    func_801EF0B0();
    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0x25 : 0x15;
    GFX_AddDitheredDrawMode(3, tpage);
}

MATCH void func_801EEDD8(void) {
    PartyMember* task;
    u32          slot;
    u32          i;

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    g_Task->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&g_Task->pos, &g_BattleEffectBattler->pos);
    Battle_ProjectRange();
    func_800B0118();
    g_Task->unk_2E.half += g_Task->unk_0C;
    g_Task->unk_30.half += g_Task->unk_10;
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 8;
    g_Task->timer        = 16;
    g_Task->header.mode++;
    for (i = 0; i < 32; i++) {
        slot                                   = BMagic_AllocEffect() & BYTE_MASK;
        task                                   = g_Task;
        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[slot].unk_04       = i;
        BMAGIC_EFFECT_SLOTS[slot].unk_0B       = 0;
        BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = i * 4 + 1;
        BMAGIC_EFFECT_SLOTS[slot].target.party = task;
        g_Task->param.unk_0B++;
    }
    SND_QueueSelectionEffect(0x100);
}

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

MATCH void func_801EEFF0(void) {
    u8 timer_next;

    if (g_Task->param.unk_0B < 3U) {
        timer_next    = g_Task->timer - 1;
        g_Task->timer = timer_next;
        if (!(timer_next & BYTE_MASK)) {
            g_Task->header.mode += 1;
        }
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EF0B0(void) {
    POLY_G3* poly;
    s32      radius;
    u8       red;
    u8       green;
    u8       blue;
    u8       i;

    i    = 0;
    blue = red = green = g_Task->timer * 15;
    radius             = (rand() & 3) | 0x20;
    do {
        poly = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(poly);
        SetSemiTrans(poly, 1);
        setXY3(poly, g_Task->unk_2E.half, g_Task->unk_30.half, g_Task->unk_2E.half + ((rsin(i << 9) * radius) >> 12), g_Task->unk_30.half + ((rcos(i << 9) * radius) >> 12),
               g_Task->unk_2E.half + ((rsin((i + 1) << 9) * radius) >> 12), g_Task->unk_30.half + ((rcos((i + 1) << 9) * radius) >> 12));
        setRGB0(poly, red, green, blue);
        setRGB1(poly, 1, 1, 1);
        setRGB2(poly, 1, 1, 1);
        GFX_AddPrim(3, sizeof(POLY_G3));
        i++;
    } while (i < 8);
}

MATCH void func_801EF268(void) {
}

/* func_801EF270 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF2B4(void) {
    u8           slot;
    PartyMember* battler;

    SYS_DISPATCH_TASK(g_BMagicEffectModes + 2, 2, g_Task);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        g_Task->param.unk_0B++;
        func_801EF6E8();
        if ((g_Task->param.unk_0B & 3) == 0) {
            if (g_Task->header.step == 1) {
                if (g_Task->timer != 0) {
                    slot = BMagic_AllocEffect();
                    if (slot != 0xFF) {
                        battler                                = g_BattleEffectBattler;
                        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 1;
                        BMAGIC_EFFECT_SLOTS[slot].target.party = battler;
                        BMAGIC_EFFECT_SLOTS[slot].unk_2E       = D_1F800000.view.effect.params[4];
                        BMAGIC_EFFECT_SLOTS[slot].unk_30       = D_1F800000.view.effect.params[5];
                        g_BattleEffectBattler->param.unk_0B++;
                    }
                }
            }
        }
    }
}

MATCH void func_801EF3FC(void) {
    PartyMember* battler;

    if (--g_Task->unk_09 == 0) {
        Battle_CenterCamera();
        Battle_ProjectRange();
        battler                          = g_BattleEffectBattler;
        D_1F800000.view.effect.params[6] = g_Task->unk_2E.half;
        D_1F800000.view.effect.params[7] = g_Task->unk_30.half;
        D_1F800000.view.effect.params[4] = g_Task->unk_2E.half = battler->unk_2E.half;
        D_1F800000.view.effect.params[5] = g_Task->unk_30.half = battler->unk_30.half;
        g_Task->unk_14 = ratan2(D_1F800000.view.effect.params[6] - D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[7] - D_1F800000.view.effect.params[5]);
        if (g_Task->unk_04 & 1) {
            g_Task->unk_14 += (rand() & 7) << 6;
        } else {
            g_Task->unk_14 -= (rand() & 7) << 6;
        }
        g_Task->unk_0C       = 0;
        g_Task->param.unk_0B = rand() & 0x3F;
        g_Task->unk_09       = 0x10;
        g_Task->timer        = 0;
        g_Task->header.step++;
    }
}

MATCH void func_801EF588(void) {
    u8 timer;

    timer         = g_Task->timer + 4;
    g_Task->timer = timer;
    if (timer == 16) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EF5D8(void) {
    g_Task->timer = 16 + (rsin((g_Task->param.unk_0B & 0x3F) << 6) * 4 >> 12);
    g_Task->unk_0C++;
    if (g_Task->unk_0C == 0x10) {
        g_Task->header.step++;
    }
}

MATCH void func_801EF654(void) {
    u8 timer;

    g_Task->timer  = ((rsin((g_Task->param.unk_0B & 0x3F) << 6) * 4) >> 0xC) + 16;
    timer          = g_Task->unk_09 - 2;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801EF6E8);

MATCH void func_801F020C(void) {
    SYS_DISPATCH_BYTE(D_801F08F4, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F03E0();
        func_801F05B4();
    }
}

MATCH void func_801F028C(void) {
    g_Task->unk_5D = 8;
    g_Task->unk_5E = 6;
    g_Task->unk_5F = 15;
    g_Task->unk_09 = 0;
    g_Task->timer  = 2;
    g_Task->header.step++;
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

    red    = g_Task->unk_09 * (s8)g_Task->unk_5D;
    green  = g_Task->unk_09 * (s8)g_Task->unk_5E;
    i      = 0;
    centre = g_Task->unk_09 * 15;
    radius = g_Task->timer * 2;
    blue   = g_Task->unk_09 * (s8)g_Task->unk_5F;
    do {
        poly = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(poly);
        SetSemiTrans(poly, 1);
        setXY3(poly, g_Task->unk_2E.half, g_Task->unk_30.half, g_Task->unk_2E.half + ((rsin(i << 9) * radius) >> 12), g_Task->unk_30.half + ((rcos(i << 9) * radius) >> 12),
               g_Task->unk_2E.half + ((rsin((i + 1) << 9) * radius) >> 12), g_Task->unk_30.half + ((rcos((i + 1) << 9) * radius) >> 12));
        setRGB0(poly, centre, centre, centre);
        setRGB1(poly, red, green, blue);
        setRGB2(poly, red, green, blue);
        GFX_AddPrim(3, sizeof(POLY_G3));
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

    red   = g_Task->unk_09 * (s8)g_Task->unk_5D;
    green = g_Task->unk_09 * (s8)g_Task->unk_5E;
    i     = 0;
    outer = g_Task->timer * 3;
    inner = g_Task->timer * 2;
    blue  = g_Task->unk_09 * (s8)g_Task->unk_5F;
    do {
        poly = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(poly);
        SetSemiTrans(poly, 1);
        setXY4(poly, g_Task->unk_2E.half + ((rsin(i << 9) * outer) >> 12), g_Task->unk_30.half + ((rcos(i << 9) * outer) >> 12), g_Task->unk_2E.half + ((rsin((i + 1) << 9) * outer) >> 12),
               g_Task->unk_30.half + ((rcos((i + 1) << 9) * outer) >> 12), g_Task->unk_2E.half + ((rsin(i << 9) * inner) >> 12), g_Task->unk_30.half + ((rcos(i << 9) * inner) >> 12),
               g_Task->unk_2E.half + ((rsin((i + 1) << 9) * inner) >> 12), g_Task->unk_30.half + ((rcos((i + 1) << 9) * inner) >> 12));
        setRGB0(poly, 1, 1, 1);
        setRGB1(poly, 1, 1, 1);
        setRGB2(poly, red, green, blue);
        setRGB3(poly, red, green, blue);
        GFX_AddPrim(3, sizeof(POLY_G4));
        i++;
    } while (i < 8);
}

/* func_801F0828 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F088C */
#include "overlays/bmagic/Actor_Clear.h"
