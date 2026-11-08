#include "magic003_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC28);

/* blocker: running-offset indexing; first diff: retail move v1,zero at +4 against a lui base. */
/* blocker: the clear loop over the 0x78-stride table at D_801F0B38 needs its record type; first diff: lui at the table address at 0x801EED14. */
INCLUDE_ASM(func_801EED14);

MATCH void func_801EEDAC(void) {
    u8 temp_v0;

    func_801F07B0(1);
    func_801F0164(1);
    temp_v0        = g_Task->unk_09 - 1;
    g_Task->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_Task->unk_09 = 0x1E;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEE28(void) {
    u8 temp_v0;

    func_801F07B0(2);
    func_801F0164(2);
    temp_v0        = g_Task->unk_09 - 1;
    g_Task->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_Task->unk_09 = 0xA;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEEA4(void) {
    u8 count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        g_Task->param.unk_0B = rand() & 3;
        if (g_Task->timer < 16) {
            g_Task->unk_09 = D_801F0A84[g_Task->timer];
        } else {
            g_Task->unk_09 = 3;
        }
        g_Task->header.mode += 1;
    }
}

INCLUDE_ASM(func_801EEF4C);

MATCH void func_801EF04C(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->unk_09      = 0x1E;
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

MATCH void func_801EF0A8(void) {
    u8 temp_v0;

    func_801F07B0(0);
    func_801F0550(g_Task->timer);
    func_801F0164(0);
    temp_v0        = g_Task->unk_09 - 1;
    g_Task->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_Task->header.mode += 1;
    }
}

INCLUDE_ASM(func_801EF12C);

MATCH void func_801EF1FC(void) {
    if (g_Task->param.unk_0B == 0) {
        *D_8014637C &= 0xBF;
        func_800AEF98(4, 0);
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EF268(void) {
    SND_QueueSelectionFx(258);
    D_801463D6 = g_Task->timer;
    func_800A9820(g_BattleTargetSelector);
    g_BattleState = g_BattleState | BATTLE_STATE_EFFECT_PLAYING;
    func_801E5988();
}

MATCH void func_801EF2CC(void) {
    Callback handlers[2] = {func_801EF324, func_801EF708};

    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

MATCH void func_801EF324(void) {
    Magic003Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.step != 0 && g_Task->header.flags != 0) {
        Area_SetDrawMode();
    }
}

MATCH void func_801EF3C8(void) {
    s32 temp_x;
    s32 temp_a1;
    u32 temp_a2;
    u8  temp_v0;

    temp_v0        = g_Task->unk_09 - 1;
    g_Task->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        temp_x          = g_Task->pos.x.fixed;
        temp_a1         = g_Task->pos.y.fixed;
        temp_a2         = g_Task->pos.z.fixed;
        g_Task->unk_0C  = 0x2000;
        g_Task->unk_14  = 0x300000;
        g_Task->unk_10  = 0;
        g_Task->unk_20  = -0x80000;
        g_Task->unk_18  = temp_x;
        g_Task->unk_1C  = temp_a1;
        g_Task->scale.y = temp_a2;
        func_801DD350(g_Task);
        g_Task->unk_09 = func_800AFF98();
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF478(void) {
    s32 value;
    u8  value2;

    value2 = g_Task->unk_09;
    value  = value2 & 0xFF;
    if (value != 0) {
        if (value != 0xFF) {
            g_Task->unk_09 = value2 - 1;
        }
    } else {
        SND_QueueSelectionFx(0x101);
        func_800AFC98(2, 0);
        func_801F0078();
        func_800A9610(g_BattleTargetSelector, 0x10U);
        g_Task->unk_09 = 0xFF;
    }
    g_Task->pos.x.fixed += g_Task->unk_0C;
    g_Task->pos.y.fixed += g_Task->unk_10;
    g_Task->pos.z.fixed += g_Task->unk_14;
    g_Task->unk_14 += g_Task->unk_20;
    func_8014DAEC();
    if (g_Task->pos.z.fixed == g_Task->scale.y) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF578(void) {
    s32 value;
    u8  value2;

    value2 = g_Task->unk_09;
    value  = value2 & 0xFF;
    if (value != 0) {
        if (value != 0xFF) {
            g_Task->unk_09 = value2 - 1;
        }
    } else {
        SND_QueueSelectionFx(0x101);
        func_800AFC98(2, 0);
        func_801F0078();
        func_800A9610(g_BattleTargetSelector, 0x10U);
        g_Task->unk_09 = 0xFF;
    }
    func_8014DAEC();
    if (g_Task->unk_09 == 0xFF) {
        g_Task->unk_0C = -0x2000;
        g_Task->unk_10 = 0;
        func_801DD350(g_Task);
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF644(void) {
    g_Task->pos.x.fixed += g_Task->unk_0C;
    g_Task->pos.y.fixed += g_Task->unk_10;
    func_8014DAEC();
    if (g_Task->pos.x.fixed == g_Task->unk_18 && g_Task->pos.y.fixed == g_Task->unk_1C) {
        g_Task->header.step++;
    }
}

MATCH void func_801EF6CC(void) {
    PartyMember* work;
    u8           step;

    work = BATTLE_ACTIVE_WORK;
    step = work->param.unk_0B;
    if (step < 2) {
        work->param.unk_0B = step - 1;
        func_801E5988();
    }
}

MATCH void func_801EF708(void) {
    Magic003SecondSteps handlers;

    handlers = D_801EEC18;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.step != 0 && g_Task->header.flags != 0) {
        Area_SetDrawMode();
    }
}

INCLUDE_ASM(func_801EF7A8);

MATCH void func_801EF918(void) {
    g_Task->pos.x.fixed += g_Task->unk_0C;
    g_Task->pos.y.fixed += g_Task->unk_10;
    g_Task->pos.z.fixed += g_Task->unk_14;
    g_Task->unk_14 += g_Task->unk_20;
    func_8014DAEC();
    if (g_Task->pos.z.fixed == g_Task->scale.y) {
        g_Task->header.step++;
    }
}

MATCH void func_801EF9AC(void) {
    g_Task->unk_0C = -0x2000;
    g_Task->unk_10 = 0;
    func_801DD350(g_Task);
    func_8014DAEC();
    g_Task->header.step += 1;
}

MATCH void func_801EF9FC(void) {
    g_Task->pos.x.fixed += g_Task->unk_0C;
    g_Task->pos.y.fixed += g_Task->unk_10;
    func_8014DAEC();
    if ((g_Task->pos.x.fixed == g_Task->unk_18) && (g_Task->pos.y.fixed == g_Task->unk_1C)) {
        GFX_FreePaletteFadeTarget(g_Task);
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EFA9C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, TASK_BYTES[1]);
}

INCLUDE_ASM(func_801EFAE0);

INCLUDE_ASM(func_801EFB8C);

MATCH void func_801EFCF8(void) {
    PartyMember* work;

    func_8014DAEC();
    if (func_8014DAEC() != 0u) {
        work               = (PartyMember*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801EFD4C);

INCLUDE_ASM(func_801EFEC8);

INCLUDE_ASM(func_801F0078);

INCLUDE_ASM(func_801F0164);

INCLUDE_ASM(func_801F03F0);

INCLUDE_ASM(func_801F0550);

INCLUDE_ASM(func_801F07B0);

/* func_801F09C4 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0A28 */
MATCH void Actor_Clear(void) {
    BMagic_ResetLocalWork();
}
