#include "magic158_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_RunSlotsWithSetup.h"

INCLUDE_ASM(func_801EED04);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEEF0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF34(void) {
    SYS_DISPATCH_BYTE(D_801EF788, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF2F0();
        func_801EF3EC();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EEFBC);

MATCH void func_801EF140(void) {
    u8 count;
    u8 timer;

    count                    = g_Task->unk_09;
    COORD_INT(g_Task->pos.z) = COORD_INT(g_Task->pos.z) - 0x60;
    if ((count & BYTE_MASK) != 0x10) {
        g_Task->unk_09 = count + 1;
    }
    timer = g_Task->timer;
    if (timer != 16) {
        g_Task->timer = timer + 2;
    }
    if (COORD_INT(g_Task->pos.z) == COORD_INT(BATTLE_ACTIVE_WORK->pos.z)) {
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF1C8);

MATCH void func_801EF2F0(void) {
    SVECTOR      pos;
    SVECTOR      rot;
    MATRIX       matrix;
    long         flags;
    PartyMember* work;
    s32          roll;

    PushMatrix();
    work   = g_Task;
    rot.vx = 0x400;
    rot.vy = 0xE00;
    if (work->param.unk_0B & 1) {
        roll = g_FrameCount ^ 0x1F;
    } else {
        roll = g_FrameCount;
    }
    rot.vz = (roll & 0x1F) << 7;
    FAKE_BARRIER(); /* FAKE: keeps the roll store before the position load. */
    pos.vx = (g_Task->pos.x.fixed >> 9) - 0x4000;
    pos.vy = (g_Task->pos.y.fixed >> 9) - 0x4000;
    pos.vz = -COORD_INT(g_Task->pos.z) / 2;
    RotTrans(&pos, (VECTOR*)matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2(&g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

INCLUDE_ASM(func_801EF3EC);

/* func_801EF708 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
