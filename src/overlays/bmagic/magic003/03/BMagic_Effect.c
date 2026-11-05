#include "magic003_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC28);

/* nonmatching: clears bytes +0, +1 and +2 of 32 rows (stride 0x78) at D_801F0B38, then sets the work cell (unk_2E 0xA0, unk_30 0x70, unk_0B 0, unk_09 0x1E, unk_0A 0) and steps. Struct rows, one u8 array and three u8 arrays all keep the row bases in registers (first differing instruction: retail move v1,zero at +4 against a lui base); retail indexes with one running offset in v1 and a lui/addu pair per store. */
INCLUDE_ASM(func_801EED14);

MATCH void func_801EEDAC(void) {
    u8 temp_v0;

    func_801F07B0(1);
    func_801F0164(1);
    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_SpadWork->word_08.byte.unk_09 = 0x1E;
        g_SpadWork->step_01 += 1;
    }
}

MATCH void func_801EEE28(void) {
    u8 temp_v0;

    func_801F07B0(2);
    func_801F0164(2);
    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_SpadWork->word_08.byte.unk_09 = 0xA;
        g_SpadWork->step_01 += 1;
    }
}

INCLUDE_ASM(func_801EEEA4);

INCLUDE_ASM(func_801EEF4C);

MATCH void func_801EF04C(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0) {
        g_SpadWork->word_08.byte.unk_09 = 0x1E;
        g_SpadWork->step_01             = g_SpadWork->step_01 + 1;
    }
}

MATCH void func_801EF0A8(void) {
    u8 temp_v0;

    func_801F07B0(0);
    func_801F0550(g_SpadWork->word_08.byte.timer_0A);
    func_801F0164(0);
    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_SpadWork->step_01 += 1;
    }
}

INCLUDE_ASM(func_801EF12C);

MATCH void func_801EF1FC(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        D_8014637C->flags_00 &= 0xBF;
        func_800AEF98(4, 0);
        g_SpadWork->step_01 += 1;
    }
}

MATCH void func_801EF268(void) {
    SND_QueueSelectionFx(258);
    D_801463D6 = g_SpadWork->word_08.byte.timer_0A;
    func_800A9820(g_BattleTargetSelector);
    g_BattleState = g_BattleState | 4;
    func_801E5988();
}

MATCH void func_801EF2CC(void) {
    Callback handlers[2] = {func_801EF324, func_801EF708};

    SYS_DISPATCH_TASK(handlers, 1, g_SpadWork);
}

MATCH void func_801EF324(void) {
    BattleHandlerTable5 handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.handlers, g_SpadWork->unk_02);
    if (g_SpadWork->unk_02 != 0 && g_SpadWork->flags_00 != 0) {
        Area_SetDrawMode();
    }
}

MATCH void func_801EF3C8(void) {
    s32 temp_x;
    s32 temp_a1;
    u32 temp_a2;
    u8  temp_v0;

    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        temp_x             = g_SpadWork->coord_x_34.raw;
        temp_a1            = g_SpadWork->coord_y_38.raw;
        temp_a2            = g_SpadWork->word_3C.word;
        g_SpadWork->unk_0C = 0x2000;
        g_SpadWork->unk_14 = 0x300000;
        g_SpadWork->unk_10 = 0;
        g_SpadWork->unk_20 = -0x80000;
        g_SpadWork->unk_18 = temp_x;
        g_SpadWork->unk_1C = temp_a1;
        g_SpadWork->unk_44 = (s32)temp_a2;
        func_801DD350(g_SpadWork);
        g_SpadWork->word_08.byte.unk_09 = func_800AFF98();
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF478(void) {
    s32 value;
    u8  value2;

    value2 = g_SpadWork->word_08.byte.unk_09;
    value  = value2 & 0xFF;
    if (value != 0) {
        if (value != 0xFF) {
            g_SpadWork->word_08.byte.unk_09 = value2 - 1;
        }
    } else {
        SND_QueueSelectionFx(0x101);
        func_800AFC98(2, 0);
        func_801F0078();
        func_800A9610(g_BattleTargetSelector, 0x10U);
        g_SpadWork->word_08.byte.unk_09 = 0xFF;
    }
    g_SpadWork->coord_x_34.raw += g_SpadWork->unk_0C;
    g_SpadWork->coord_y_38.raw += g_SpadWork->unk_10;
    g_SpadWork->word_3C.word += g_SpadWork->unk_14;
    g_SpadWork->unk_14 += g_SpadWork->unk_20;
    func_8014DAEC();
    if (g_SpadWork->word_3C.word == g_SpadWork->unk_44) {
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF578(void) {
    s32 value;
    u8  value2;

    value2 = g_SpadWork->word_08.byte.unk_09;
    value  = value2 & 0xFF;
    if (value != 0) {
        if (value != 0xFF) {
            g_SpadWork->word_08.byte.unk_09 = value2 - 1;
        }
    } else {
        SND_QueueSelectionFx(0x101);
        func_800AFC98(2, 0);
        func_801F0078();
        func_800A9610(g_BattleTargetSelector, 0x10U);
        g_SpadWork->word_08.byte.unk_09 = 0xFF;
    }
    func_8014DAEC();
    if (g_SpadWork->word_08.byte.unk_09 == 0xFF) {
        g_SpadWork->unk_0C = -0x2000;
        g_SpadWork->unk_10 = 0;
        func_801DD350(g_SpadWork);
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF644(void) {
    g_SpadWork->coord_x_34.raw += g_SpadWork->unk_0C;
    g_SpadWork->coord_y_38.raw += g_SpadWork->unk_10;
    func_8014DAEC();
    if (g_SpadWork->coord_x_34.raw == g_SpadWork->unk_18 && g_SpadWork->coord_y_38.raw == g_SpadWork->unk_1C) {
        g_SpadWork->unk_02++;
    }
}

MATCH void func_801EF6CC(void) {
    PartyBattler* work;
    u8            step;

    work = BATTLE_ACTIVE_WORK;
    step = work->word_08.byte.unk_0B;
    if (step < 2) {
        work->word_08.byte.unk_0B = step - 1;
        func_801E5988();
    }
}

MATCH void func_801EF708(void) {
    MagicTaskFuncs handlers;

    handlers = D_801EEC18;
    SYS_DISPATCH_BYTE(handlers.handlers, g_SpadWork->unk_02);
    if (g_SpadWork->unk_02 != 0 && g_SpadWork->flags_00 != 0) {
        Area_SetDrawMode();
    }
}

INCLUDE_ASM(func_801EF7A8);

MATCH void func_801EF918(void) {
    g_SpadWork->coord_x_34.raw += g_SpadWork->unk_0C;
    g_SpadWork->coord_y_38.raw += g_SpadWork->unk_10;
    g_SpadWork->word_3C.word += g_SpadWork->unk_14;
    g_SpadWork->unk_14 += g_SpadWork->unk_20;
    func_8014DAEC();
    if (g_SpadWork->word_3C.word == g_SpadWork->unk_44) {
        g_SpadWork->unk_02++;
    }
}

MATCH void func_801EF9AC(void) {
    g_SpadWork->unk_0C = -0x2000;
    g_SpadWork->unk_10 = 0;
    func_801DD350(g_SpadWork);
    func_8014DAEC();
    g_SpadWork->unk_02 += 1;
}

MATCH void func_801EF9FC(void) {
    g_SpadWork->coord_x_34.raw += g_SpadWork->unk_0C;
    g_SpadWork->coord_y_38.raw += g_SpadWork->unk_10;
    func_8014DAEC();
    if ((g_SpadWork->coord_x_34.raw == g_SpadWork->unk_18) && (g_SpadWork->coord_y_38.raw == g_SpadWork->unk_1C)) {
        func_80196718(g_SpadWork);
        D_801EB4E0->word_08.byte.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EFA9C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EFAE0);

INCLUDE_ASM(func_801EFB8C);

MATCH void func_801EFCF8(void) {
    PartyBattler* work;

    func_8014DAEC();
    if (func_8014DAEC() != 0u) {
        work                      = (PartyBattler*)D_801EB4E0;
        work->word_08.byte.unk_0B = work->word_08.byte.unk_0B - 1;
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
    Bmagic_ResetLocalWork();
}
