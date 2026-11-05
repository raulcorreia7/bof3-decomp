#include "magic078_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EECFC);

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

MATCH void func_801EEEE4(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

INCLUDE_ASM(func_801EEF28);

MATCH void func_801EF08C(void) {
    u8 temp_a1;

    temp_a1 = g_Task->unk_09;
    if ((temp_a1 & 0xFF) == 0xC) {
        g_Task->timer = 0xF;
        g_Task->step += 1;
        return;
    }
    g_Task->unk_09 = temp_a1 + 1;
}

#include "overlays/bmagic/Effect_CountDownAndStep.h"

MATCH void func_801EF12C(void) {
    s32 temp_v0;
    s32 var_v0;
    s32 var_v1;

    temp_v0 = ratan2(g_BattleSelectedActor->pos.y.fixed - g_Task->pos.y.fixed,
                     g_BattleSelectedActor->pos.x.fixed - g_Task->pos.x.fixed);
    var_v1  = g_Task->unk_0C;
    if (var_v1 < 0) {
        var_v1 += 0x3F;
    }
    var_v1 >>= 6;
    var_v0 = temp_v0 & 0xFFF;
    if (var_v0 < 0) {
        var_v0 += 0x3F;
    }
    if (var_v1 == (var_v0 >> 6)) {
        g_Task->timer = 0xF;
        g_Task->step += 1;
    }
}

MATCH void func_801EF1CC(void) {
    u8 count;

    count         = g_Task->timer - 1;
    g_Task->timer = count;
    if (count == 0) {
        BATTLE_ACTIVE_WORK->unk_0B = 1;
        g_Task->step               = g_Task->step + 1;
    }
}

MATCH void func_801EF228(void) {
    if (D_801EB4E0->unk_0B == 2) {
        g_Task->timer = 0;
        g_Task->step += 1;
    }
}

MATCH void func_801EF278(void) {
    g_Task->timer += 8;
    if ((u8)g_Task->timer >= 0x81U) {
        g_Task->step += 1;
    }
}

MATCH void func_801EF2CC(void) {
    u8 temp_v0;

    temp_v0        = g_Task->unk_09 - 1;
    g_Task->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        D_801EB4E0->unk_0B = 0xFF;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF318);

INCLUDE_ASM(func_801EFE14);

MATCH void func_801EFEB8(void) {
    PartyBattler* work;
    SVECTOR       pos;
    SVECTOR       rot;
    MATRIX        matrix;
    long          flags;

    PushMatrix();
    work   = g_Task;
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = 0;
    if (work->slot == 0xD) {
        rot.vz = work->unk_0C;
    }
    pos.vx = (work->pos.x.fixed >> 9) - 0x4000;
    pos.vy = (work->pos.y.fixed >> 9) - 0x4000;
    pos.vz = -work->pos.z.part.integer / 2;
    RotTrans(&pos, &matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2((MATRIX*)g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

INCLUDE_ASM(func_801EFF84);

INCLUDE_ASM(func_801F00A0);

MATCH void func_801F00EC(void) {
    u8 temp_a0;

    temp_a0 = g_Task->unk_09;
    if ((temp_a0 & 0xFF) == 8) {
        SND_QueueSelectionFx(0x101);
        g_Task->step += 1;
        return;
    }
    g_Task->unk_09 = temp_a0 + 1;
}

MATCH void func_801F014C(void) {
    func_800AF2B4(D_801EB4E0, 0x30);
    g_Task->pos.z.part.integer = (u16)g_Task->pos.z.part.integer + 0x10;
    if (func_800AF5FC(D_801EB4E0, 0x1C000) != 0) {
        g_Task->timer = 0x1E;
        g_Task->step += 1;
    }
}

MATCH void func_801F01D0(void) {
    PartyBattler* work;

    work        = g_Task;
    work->timer = work->timer - 1;
    if (work->timer == 0) {
        SND_QueueSelectionFx(0x102);
        g_Task->step = g_Task->step + 1;
    }
}

INCLUDE_ASM(func_801F0230);

MATCH void func_801F02B4(void) {
    u8 timer;

    timer         = g_Task->timer + 1;
    g_Task->timer = timer;
    if (timer == 8) {
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F02FC);

#include "overlays/bmagic/Effect_SetActorMatrix.h"
