#include "magic001_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EECC4);

MATCH void func_801EEF34(void) {
    BMagic_ClearWorkFlagsAndStep();
}

#include "shared/Effect_StartPlaying.h"

/* func_801EEFD8 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF01C(void) {
    Magic001Steps handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
}

MATCH void func_801EF0E8(void) {
    func_801E257C(g_Battle.active_battler, 0xAU);
    g_Task->unk_27 = g_BattleEffectBattler->unk_27;
    g_Task->unk_09 = 0;
    g_Task->timer  = 0;
    g_Task->header.step += 1;
}

MATCH void func_801EF164(void) {
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        func_800AFC98(2, 0);
        func_801E257C(g_Battle.active_battler, 0xBU);
        g_Task->unk_14 = 0x100;
        g_Task->unk_20 = -8;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF1CC);

MATCH void func_801EF280(void) {
    PartyMember* work;
    u8           timer;

    work         = g_Task;
    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    work->unk_14 += work->unk_20;
    COORD_INT(work->pos.z) += work->unk_14;
    if (timer == 0) {
        SND_QueueSelectionFx(0x203);
        func_801E257C(g_Battle.active_battler, 0xC);
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        g_Task->unk_09 = 3;
        g_Task->header.step++;
    }
}

MATCH void func_801EF324(void) {
    if (Actor_StepAnimOnce() != 0u) {
        func_801E257C(g_Battle.active_battler, 0xA);
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EF37C(void) {
    PartyMember* work;

    Actor_StepAnimOnce();
    Actor_StepAnimOnce();
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        func_800AFC98(2, 0);
        func_801E257C(g_Battle.active_battler, 0xB);
        work         = g_Task;
        work->unk_14 = 0x140;
        work->timer  = 9;
        work->unk_20 = -0x40;
        g_Task->header.step++;
    }
}

MATCH void func_801EF408(void) {
    PartyMember* work  = g_Task;
    u8           timer = work->timer - 1;
    s32          value = work->unk_14 + work->unk_20;
    work->timer        = timer;
    work->unk_14       = value;
    COORD_INT(work->pos.z) += value;
    if (timer == 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF468(void) {
    u8 timer;

    Actor_StepAnimOnce();
    Actor_StepAnimOnce();
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        SND_QueueSelectionFx(0x203);
        func_801E257C(g_Battle.active_battler, 0xC);
        timer          = g_Task->unk_09 - 1;
        g_Task->unk_09 = timer;
        if (timer != 0) {
            g_Task->header.step -= 3;
        } else {
            g_Task->header.step++;
        }
    }
}

MATCH void func_801EF518(void) {
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        g_Task->unk_5C = 1;
        g_Task->unk_5D = 0;
        g_Task->unk_5E = 0;
        g_Task->unk_5F = 0;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF5CC);

#include "overlays/bmagic/Effect_RampTintAndFinish.h"

MATCH void func_801EF688(void) {
    EFFECT_RAMP_TINT_AND_FINISH();
}

MATCH void func_801EF72C(void) {
    Magic001SecondSteps handlers;

    handlers = D_801EEC3C;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);
}

INCLUDE_ASM(func_801EF78C);

MATCH void func_801EFA14(void) {
    BMagic_ClearWorkFlagsAndStep();
}

MATCH void Effect_StartPlaying6(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}

MATCH void func_801EFAB8(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 1), 1, g_Task);
}

MATCH void func_801EFAFC(void) {
    Callback handlers[7];

    __builtin_memcpy(handlers, D_801EEC48, sizeof(handlers));
    SYS_DISPATCH_BYTE(handlers, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
        if (g_Task->header.step < 5) {
            func_801F014C();
            func_801F0238();
            PopMatrix();
        }
    }
}

MATCH void func_801EFBEC(void) {
    g_Task->unk_27 = g_BattleEffectBattler->unk_27;
    g_Task->unk_14 = 0x100;
    g_Task->unk_20 = -0x10;
    g_Task->unk_09 = 0;
    g_Task->timer  = 16;
    g_Task->header.step += 1;
}

INCLUDE_ASM(func_801EFC54);

MATCH void func_801EFD28(void) {
    s32 value;
    u8  timer;
    u8  next;

    timer                    = g_Task->timer;
    value                    = g_Task->unk_14 + g_Task->unk_20;
    g_Task->unk_14           = value;
    COORD_INT(g_Task->pos.z) = COORD_INT(g_Task->pos.z) + value;
    if (timer < 8U) {
        g_Task->timer = timer + 1;
    }
    next           = g_Task->unk_09 - 1;
    g_Task->unk_09 = next;
    if (!(next & BYTE_MASK)) {
        func_800AFC98(2, 0);
        SND_QueueSelectionFx(0x203);
        g_Task->unk_14 = 0x40;
        g_Task->unk_20 = -8;
        g_Task->unk_0C = ratan2(g_BattleEffectBattler->pos.x.fixed - g_Task->pos.x.fixed, g_BattleEffectBattler->pos.y.fixed - g_Task->pos.y.fixed);
        /* FAKE: Without the barrier, the scheduler sinks the angle store into the call's delay slot. */
        FAKE_BARRIER();
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Task->unk_09 = 0x10;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFE38(void) {
    s32 value;
    u8  value2;
    u8  value3;

    g_Task->pos.x.fixed += (rsin(g_Task->unk_0C) << 0xD) >> 0xC;
    g_Task->pos.y.fixed += (rcos(g_Task->unk_0C) << 0xD) >> 0xC;
    value                    = g_Task->unk_14 + g_Task->unk_20;
    g_Task->unk_14           = value;
    COORD_INT(g_Task->pos.z) = COORD_INT(g_Task->pos.z) + value;
    if (g_Task->unk_09 < 8U) {
        value3 = g_Task->timer;
        if (value3 < 0x10U) {
            g_Task->timer = value3 + 1;
        }
    }
    value2         = g_Task->unk_09 - 1;
    g_Task->unk_09 = value2;
    if (!(value2 & BYTE_MASK)) {
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_PrimeTintOnScriptReady.h"

MATCH void func_801EFFCC(void) {
    PartyMember* work;
    PartyMember* source;
    s8           count;
    u8           timer;

    count = g_Task->unk_5D;
    if (count != -0x80) {
        g_Task->unk_5D = count - 0x10;
        g_Task->unk_5E -= 16;
        g_Task->unk_5F -= 16;
    }
    timer = g_Task->timer;
    if (timer != 0) {
        g_Task->timer = timer - 2;
    }
    if ((s8)g_Task->unk_5D == -128) {
        work   = g_Task;
        source = BATTLE_ACTIVE_WORK;
        WorldPos_Copy(&work->pos, &source->pos);
        work->header.step += 1;
    }
}

MATCH void func_801F00A8(void) {
    EFFECT_RAMP_TINT_AND_FINISH();
}

INCLUDE_ASM(func_801F014C);

MATCH void func_801F0238(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    if (GetGraphType() == 1) {
        tpage = 0x125;
    } else if (GetGraphType() == 2) {
        tpage = 0x125;
    } else {
        tpage = 0x55;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    D_1F800000.view.effect.params[1] = g_Task->timer << 3;
    D_1F800000.view.effect.params[0] = g_Task->timer << 3;
    D_1F800014[2].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);

    for (i = 1; i <= 16; i++) {
        prim             = GFX_BeginPolyG3(1);
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vz = 0;
        D_1F800014[1].vz = 0;
        D_1F800014[0].vz = 0;
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, D_1F800000.view.effect.params[1], D_1F800000.view.effect.params[1], D_1F800000.view.effect.params[1]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(5, sizeof(POLY_G3));
    }

    if (GetGraphType() == 1) {
        tpage = 0x25;
    } else if (GetGraphType() == 2) {
        tpage = 0x25;
    } else {
        tpage = 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
}
