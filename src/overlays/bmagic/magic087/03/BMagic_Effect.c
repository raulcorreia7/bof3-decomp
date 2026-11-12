#include "magic087_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_RunSlotsWithSetup.h"

INCLUDE_ASM(func_801EED04);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EF0A8 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF0EC(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 1), 2, g_Task);
}

INCLUDE_ASM(func_801EF130);

MATCH void func_801EF2C0(void) {
    if (g_Task->param.unk_0B == 2) {
        g_Task->unk_04 = 0;
        g_Task->unk_09 = 8;
        g_Task->timer  = 16;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF324);

MATCH void func_801EF4A0(void) {
    u8 counter;

    counter        = g_Task->unk_09 + 1;
    g_Task->unk_09 = counter;
    if ((counter & BYTE_MASK) == 0x10) {
        g_Task->header.step += 1;
        return;
    }
    g_Task->unk_04 += 1;
    Battle_ProjectRange();
    func_801EF580(0);
    func_801EF580(0xF);
}

MATCH void func_801EF530(void) {
    PartyMember* work;

    if (g_Task->param.unk_0B == 0x80) {
        work               = (PartyMember*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF580);

MATCH void func_801EF958(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 6), 1, g_Task);
}

MATCH void func_801EF99C(void) {
    SYS_DISPATCH_BYTE(D_801F0530, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        if (g_Task->header.step != 0 && g_Task->header.step != 3) {
            func_801EFF50();
            func_801F0014();
            PopMatrix();
        }
    }
}

MATCH void func_801EFA2C(void) {
    u8 value;

    value          = g_Task->unk_09 - 1;
    g_Task->unk_09 = value;
    if (!(value & BYTE_MASK)) {
        g_Task->unk_0C = 0x100;
        g_Task->unk_18 = 4;
        if (g_Task->header.mode != 0) {
            g_Task->param.unk_0B = 0;
            g_Task->unk_09       = 0;
        } else {
            g_Task->param.unk_0B = 8;
            g_Task->unk_09       = 0x1F;
        }
        g_Task->timer = 0;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EFAD4);

MATCH void func_801EFCA0(void) {
    PartyMember* active;
    PartyMember* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->param.unk_0B == 130) {
        work              = SP_REF(PartyMember*, 0x44u);
        work->header.step = work->header.step + 1;
    }
}

MATCH void func_801EFCE0(void) {
    u8 timer;

    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (!(timer & BYTE_MASK)) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        g_Task->header.flags = 0;
        g_Task->header.mode  = 0;
        g_Task->header.step  = 0;
        g_Task->unk_03       = 0;
        g_Task->unk_04       = 0;
    }
}

MATCH void func_801EFD7C(void) {
    SYS_DISPATCH_BYTE(D_801F0540, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EFF50();
        func_801F0014();
        PopMatrix();
    }
}

MATCH void func_801EFE04(void) {
    g_Task->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed;
    g_Task->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed;
    g_Task->pos.z.fixed = BATTLE_ACTIVE_WORK->pos.z.fixed;
    if (g_Task->header.mode == 2) {
        g_Task->param.unk_0B = 0;
    } else {
        g_Task->param.unk_0B = 8;
    }
    g_Task->unk_09 = 0;
    g_Task->timer  = 32;
    g_Task->header.step += 1;
}

INCLUDE_ASM(func_801EFE90);

MATCH void func_801EFF50(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    ;
    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = (g_Task->param.unk_0B & 0x3f) << 6;
    pos.vx = (g_Task->pos.x.fixed >> 9) - 0x4000;
    pos.vy = (g_Task->pos.y.fixed >> 9) - 0x4000;
    pos.vz = -(COORD_INT(g_Task->pos.z) + 0x200) / 2;
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}

INCLUDE_ASM(func_801F0014);

/* func_801F04A4 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
