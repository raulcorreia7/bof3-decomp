#include "magic079_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback table[2] = {func_801EEC5C, func_801EED38};

    table[TASK_BYTES[1]]();
}

MATCH void func_801EEC5C(void) {
    u8            i;
    u32           slot;
    PartyBattler* work;

    g_Task->unk_0B = 0;
    for (i = 0; i < 4; i++) {
        slot                               = Battle_AllocEffect(1, 0x2B) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].mode         = i;
        g_BattleEffects[slot].step         = 0;
        g_BattleEffects[slot].unk_09       = 0x10;
        g_BattleEffects[slot].target.party = work;
        g_Task->unk_0B                     = g_Task->unk_0B + 1;
    }
    SND_QueueSelectionFx(0x100);
    g_Task->mode = g_Task->mode + 1;
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EED98(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

MATCH void func_801EEDDC(void) {
    SYS_DISPATCH_BYTE(D_801F02B4, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 0) {
        Effect_SetActorMatrix();
        func_801EF458();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EEE64);

INCLUDE_ASM(func_801EEEE4);

MATCH void func_801EEF34(void) {
    u8 temp_a0;
    u8 temp_v1;

    temp_a0 = g_Task->unk_09;
    if ((temp_a0 & 0xFF) != 0x20) {
        g_Task->unk_09 = temp_a0 + 1;
    }
    temp_v1       = g_Task->timer - 1;
    g_Task->timer = temp_v1;
    if ((temp_v1 & 0xFF) == 0x30) {
        g_Task->unk_09 = 0;
        g_Task->step += 1;
    }
}

MATCH void func_801EEFB8(void) {
    u8 temp_a0;
    u8 temp_v1;

    temp_a0 = g_Task->unk_09;
    if ((temp_a0 & 0xFF) != 0x20) {
        g_Task->unk_09 = temp_a0 + 1;
    }
    temp_v1       = g_Task->timer - 1;
    g_Task->timer = temp_v1;
    if ((temp_v1 & 0xFF) == 0x10) {
        D_801EB4E0->unk_0B -= 1;
        g_Task->step += 1;
    }
}

MATCH void func_801EF048(void) {
    PartyBattler* work;

    work         = g_Task;
    work->timer  = work->timer - 1;
    work         = g_Task;
    work->unk_0B = work->unk_0B - 1;
    if (work->unk_0B == 0) {
        func_801E5988();
    }
}

MATCH void func_801EF0A8(void) {
    SYS_DISPATCH_BYTE(D_801F02C8, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 0) {
        Effect_SetActorMatrix();
        func_801EF458();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF130);

MATCH void func_801EF1DC(void) {
    PartyBattler* work;
    u8            timer;

    work  = g_Task;
    timer = work->unk_09 - 1;
    COORD_INT(work->pos.z) -= 0x40;
    work->unk_09 = timer;
    if (timer == 0) {
        g_Task->unk_09 = 0x20;
        g_Task->step   = g_Task->step + 1;
    }
}

MATCH void func_801EF23C(void) {
    u8 temp_v0;
    u8 temp_v1;

    temp_v0 = g_Task->unk_09;
    if (temp_v0 != 0) {
        g_Task->unk_09 = temp_v0 - 1;
    }
    temp_v1       = g_Task->timer + 1;
    g_Task->timer = temp_v1;
    if ((temp_v1 & 0xFF) == 0x80) {
        g_Task->unk_09 = 0x20;
        g_Task->step += 1;
    }
}

MATCH void func_801EF2BC(void) {
    u8 temp_v0;
    u8 temp_v1;

    temp_v0 = g_Task->unk_09;
    if (temp_v0 != 0) {
        g_Task->unk_09 = temp_v0 - 1;
    }
    temp_v1       = g_Task->timer + 1;
    g_Task->timer = temp_v1;
    if ((temp_v1 & 0xFF) == 0xA0) {
        D_801EB4E0->unk_0B -= 1;
        g_Task->step += 1;
    }
}

MATCH void func_801EF348(void) {
    PartyBattler* work;

    work         = g_Task;
    work->timer  = work->timer + 1;
    work         = g_Task;
    work->unk_0B = work->unk_0B - 1;
    if (work->unk_0B == 0) {
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF458);

MATCH void func_801EFBEC(void) {
    SYS_DISPATCH_BYTE(D_801F035C, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 0) {
        Effect_SetActorMatrix();
        func_801F002C();
        PopMatrix();
    }
}

MATCH void func_801EFC74(void) {
    PartyBattler* src;

    src                 = g_BattleSelectedActor;
    g_Task->pos.x.fixed = src->pos.x.fixed;
    g_Task->pos.y.fixed = src->pos.y.fixed;
    g_Task->pos.z       = src->pos.z;
    g_Task->unk_09      = 4;
    g_Task->timer       = 0xB0;
    g_Task->step        = g_Task->step + 1;
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

MATCH void func_801EFD2C(void) {
    g_Task->timer -= 1;
    if (D_801EB4E0->unk_0B == g_Task->mode) {
        g_Task->step += 1;
    }
}

MATCH void func_801EFD84(void) {
    PartyBattler* work;
    PartyBattler* active;

    work         = g_Task;
    work->timer  = work->timer - 1;
    work         = g_Task;
    work->unk_09 = work->unk_09 - 1;
    if (work->unk_09 == 4) {
        active         = BATTLE_ACTIVE_WORK;
        active->unk_0B = active->unk_0B - 1;
        func_801E5988();
    }
}

MATCH void func_801EFE00(void) {
    SYS_DISPATCH_BYTE(D_801F036C, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 0) {
        Effect_SetActorMatrix();
        func_801F002C();
        PopMatrix();
    }
}

MATCH void func_801EFE88(void) {
    PartyBattler* src;
    u8            timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & 0xFF)) {
        src                 = D_8014637C;
        g_Task->pos.x.fixed = src->pos.x.fixed;
        g_Task->pos.y.fixed = src->pos.y.fixed;
        g_Task->pos.z       = src->pos.z;
        g_Task->unk_09      = 4;
        g_Task->step        = g_Task->step + 1;
    }
}

MATCH void Effect_CountUpAndStep_801EFF08(void) {
    BMAGIC_COUNT_UP_AND_STEP();
}

MATCH void func_801EFF58(void) {
    g_Task->timer += 1;
    if (D_801EB4E0->unk_0B == g_Task->mode) {
        g_Task->step += 1;
    }
}

MATCH void func_801EFFB0(void) {
    PartyBattler* work;
    PartyBattler* active;

    work         = g_Task;
    work->timer  = work->timer + 1;
    work         = g_Task;
    work->unk_09 = work->unk_09 - 1;
    if (work->unk_09 == 4) {
        active         = BATTLE_ACTIVE_WORK;
        active->unk_0B = active->unk_0B - 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F002C);
