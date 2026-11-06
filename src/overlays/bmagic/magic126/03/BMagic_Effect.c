#include "magic126_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyBattler* saved;
    PartyBattler* swap;
    s32           count;

    Bmagic_DispatchTaskPair(func_801EECE4, Effect_PlayOnZeroTick);
    count = 0;
    do {
        if (D_801F12BC[(u8)count << 5] & 1) {
            saved      = D_801EB4E0;
            swap       = FIELD(PartyBattler*, D_801F12D8, (u8)count << 5);
            D_801F22BC = D_801F12BC + ((u8)count << 5);
            D_801EB4E0 = swap;
            func_801F091C();
            D_801EB4E0 = saved;
        }
        count += 1;
    } while ((u8)count < 0x80);
}

INCLUDE_ASM(func_801EECE4);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEED0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->header.mode);
}

MATCH void func_801EEF14(void) {
    SYS_DISPATCH_BYTE(D_801F1268, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF438();
        func_801EF7A4();
        func_801EF1C8();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CopyBattlerCoords.h"

MATCH void func_801EF00C(void) {
    g_Task->unk_09 += 2;
    g_Task->timer += 24;
    if (g_Task->unk_09 == 0x10) {
        Bmagic_NextStep();
    }
}

#include "overlays/bmagic/Effect_StepWhileTickUnderTwo.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF1C8);

INCLUDE_ASM(func_801EF438);

INCLUDE_ASM(func_801EF7A4);

MATCH void func_801EFAF4(void) {
    SYS_DISPATCH_BYTE(D_801F1278, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_800AF764();
        func_801EFD5C();
    }
}

MATCH void func_801EFB74(void) {
    u8            timer = g_Task->unk_09 - 1;
    PartyBattler* work;
    PartyBattler* actor;
    s32           z;

    g_Task->unk_09 = timer;
    if (timer == 0) {
        SND_QueueSelectionFx(0x100);
        work              = g_Task;
        actor             = D_801EB4E0;
        work->pos.x.fixed = actor->pos.x.fixed;
        work->pos.y.fixed = actor->pos.y.fixed;
        z                 = actor->pos.z.fixed;
        work->unk_0B      = 0;
        work->pos.z.fixed = z;
        g_Task->unk_09    = 0x14;
        g_Task->timer     = 0;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountUpTimersAndStep.h"

MATCH void func_801EFC94(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 2;
    g_Task->unk_09 = timer;
    if (timer == 150) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTimer.h"

INCLUDE_ASM(func_801EFD5C);

MATCH void func_801F01C0(void) {
    SYS_DISPATCH_BYTE(D_801F1288, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_800AF764();
        func_801F06AC();
    }
}

INCLUDE_ASM(func_801F0240);

INCLUDE_ASM(func_801F037C);

INCLUDE_ASM(func_801F0494);

#include "overlays/bmagic/Effect_TickOnTimerNegative.h"

INCLUDE_ASM(func_801F06AC);

MATCH void func_801F091C(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 19), 1, D_801F22BC);
}

MATCH void func_801F0960(void) {
    SYS_DISPATCH_BYTE(D_801F12AC, D_801F22BC->header.step);
    if (D_801F22BC->header.flags != 0 && D_801F22BC->header.step != 0) {
        func_801F11AC();
        func_801F0ED0();
    }
}

INCLUDE_ASM(func_801F09E0);

INCLUDE_ASM(func_801F0B34);

INCLUDE_ASM(func_801F0C7C);

INCLUDE_ASM(func_801F0DA4);

INCLUDE_ASM(func_801F0ED0);

MATCH u32 func_801F1110(void) {
    u8 index;

    for (index = 0u; index < 0x80; index++) {
        if ((D_801F12BC[index << 5] & 1) == 0) {
            D_801F12BC[index << 5] |= 1;
            return index;
        }
    }
    return 0xFFu;
}

MATCH void func_801F116C(void) {
    D_801F22BC->header.flags = 0;
    D_801F22BC->header.mode  = 0;
    D_801F22BC->header.step  = 0;
    D_801F22BC->unk_03       = 0;
}

MATCH void func_801F11AC(void) {
    PartyBattler* work;
    s16           vec[3];
    TILE_1*       primitive;

    work      = D_801F22BC;
    vec[0]    = (work->unk_10 >> 9) - 0x4000;
    primitive = (TILE_1*)g_GfxPrimCursor;
    vec[1]    = (work->unk_14 >> 9) - 0x4000;
    vec[2]    = -((s16)(*(u16*)((u8*)work + 0x1A)) / 2);
    SetTile1(primitive);
    RotTransPers((SVECTOR*)vec, (long*)&primitive->x0, (long*)vec, (long*)&vec[2]);
    ((s16*)&D_801F22BC->unk_0C)[0] = primitive->x0;
    ((s16*)&D_801F22BC->unk_0C)[1] = primitive->y0;
}
