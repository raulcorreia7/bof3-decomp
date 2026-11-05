#include "magic131_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC24);

INCLUDE_ASM(func_801EEDEC);

INCLUDE_ASM(func_801EEF64);

INCLUDE_ASM(func_801EF000);

INCLUDE_ASM(func_801EF110);

INCLUDE_ASM(func_801EF1C0);

INCLUDE_ASM(func_801EF3D0);

INCLUDE_ASM(func_801EF488);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EF668(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF6AC);

INCLUDE_ASM(func_801EF7FC);

INCLUDE_ASM(func_801EFA68);

INCLUDE_ASM(func_801EFB64);

MATCH void func_801EFBF8(void) {
    u8 temp_v0;

    func_8014D978();
    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        Actor_SelectScript(1U);
        g_SpadWork->word_08.byte.unk_09 = 0x29;
        g_SpadWork->unk_02 += 1;
    }
}

INCLUDE_ASM(func_801EFC74);

MATCH void func_801EFEF0(void) {
    if (func_8014DAEC() != 0u) {
        g_SpadWork->word_08.byte.unk_09 = 0xF;
        g_SpadWork->unk_02              = g_SpadWork->unk_02 + 1;
    }
}

MATCH void func_801EFF48(void) {
    u32 direction;
    u8  timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0) {
        func_800A9820(g_BattleTargetSelector);
        direction = LOBU(g_BattleScrollDir);
        if (direction == 0 || direction == 3) {
            g_SpadWork->unk_0C = 8;
            g_SpadWork->unk_10 = -1;
            g_SpadWork->unk_18 = 1;
            g_SpadWork->unk_1C = -1;
        } else {
            g_SpadWork->unk_0C = -8;
            g_SpadWork->unk_10 = -1;
            g_SpadWork->unk_18 = -1;
            g_SpadWork->unk_1C = -1;
        }
        g_SpadWork->word_08.byte.unk_09   = 0;
        g_SpadWork->word_08.byte.timer_0A = 0x1E;
        g_SpadWork->unk_02 += 1;
    }
}

INCLUDE_ASM(func_801F0034);

MATCH void func_801F0100(void) {
    SYS_DISPATCH_BYTE(D_801F1BF4, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801F030C();
    }
}

#include "overlays/bmagic/Effect_ClearTimerNextStep.h"

#include "overlays/bmagic/Effect_CountUpByTwoAndStep.h"

MATCH void func_801F01F8(void) {
    if ((BATTLE_ACTIVE_WORK->word_08.byte.unk_09 == 0) && (EMI_LoaderIsReady() != 0)) {
        g_SpadWork->word_08.byte.timer_0A = 8;
        g_SpadWork->unk_02 += 1;
    }
}

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801F030C);

MATCH void func_801F0438(void) {
    SYS_DISPATCH_BYTE(D_801F1C08, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801F06B4();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801F04C0);

MATCH void func_801F053C(void) {
    EFFECT_ADVANCE_AT_COUNT(4, 0x40);
}

MATCH void func_801F058C(void) {
    PartyBattler* work;
    PartyBattler* active;
    s8            count;

    work = g_SpadWork;
    work->word_08.byte.unk_09 += 2;
    work         = g_SpadWork;
    count        = work->unk_5D - 4;
    work->unk_5D = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->word_08.byte.unk_0B--;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801F06B4);

MATCH void func_801F0B44(void) {
    SYS_DISPATCH_BYTE(D_801F1C24, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801F0D44();
        func_801F0DF4();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801F0BCC);

MATCH void func_801F0C4C(void) {
    s32 value;

    value              = g_SpadWork->unk_14 + 0x20;
    g_SpadWork->unk_14 = value;
    if (value == 0x200) {
        g_SpadWork->word_08.byte.unk_0B = 1;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void Effect_CountDownAndStep_801F0C98(void) {
    u8 count;

    BMAGIC_COUNT_DOWN_AND_STEP();
}

/* Best 7 differences: lui a0 at 0x801F0CE4; adjust register allocation. */
INCLUDE_ASM(func_801F0CE4);

MATCH void Effect_SetActorMatrix_801F0D44(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    BMAGIC_SET_ACTOR_MATRIX();
}

INCLUDE_ASM(func_801F0DF4);

MATCH void func_801F10F4(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 27), 1, D_801F24E0);
}

MATCH void func_801F1138(void) {
    SYS_DISPATCH_BYTE(D_801F1C48, D_801F24E0->unk_02);
    if (D_801F24E0->flags_00 != 0 && D_801F24E0->unk_02 != 0) {
        func_801F1B14();
        func_801F1844();
    }
}

INCLUDE_ASM(func_801F11B8);

INCLUDE_ASM(func_801F12A0);

INCLUDE_ASM(func_801F13A4);

INCLUDE_ASM(func_801F14A0);

INCLUDE_ASM(func_801F153C);

INCLUDE_ASM(func_801F1644);

INCLUDE_ASM(func_801F1748);

INCLUDE_ASM(func_801F1844);

INCLUDE_ASM(func_801F1A58);

MATCH void func_801F1AC4(void) {
    D_801F24E0->flags_00 = 0;
    D_801F24E0->step_01  = 0;
    D_801F24E0->unk_02   = 0;
    D_801F24E0->unk_03   = 0;
    D_801F24E0->unk_04   = 0;
}

MATCH void func_801F1B14(void) {
    PartyBattler* work;
    s16           vec[3];
    TILE_1*       primitive;

    work      = D_801F24E0;
    vec[0]    = (s16)(work->unk_14 >> 9) - 0x4000;
    primitive = (TILE_1*)g_GfxPrimCursor;
    vec[1]    = (s16)(work->unk_18 >> 9) - 0x4000;
    vec[2]    = -((s16)(*(u16*)((u8*)work + 0x1E)) / 2);
    SetTile1(primitive);
    RotTransPers((SVECTOR*)vec, (long*)&primitive->x0, (long*)vec, (long*)&vec[2]);
    ((s16*)&D_801F24E0->unk_20)[0] = primitive->x0;
    ((s16*)&D_801F24E0->unk_20)[1] = primitive->y0;
}
