#include "magic079_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    ACTOR_RUN_MODE_HANDLER(func_801EEC5C, func_801EED38);
}

MATCH void func_801EEC5C(void) {
    u8           i;
    u32          slot;
    PartyMember* work;

    g_Task->param.unk_0B = 0;
    for (i = 0; i < 4; i++) {
        slot                               = Battle_AllocEffect(1, 0x2B) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = i;
        g_BattleEffects[slot].header.step  = 0;
        g_BattleEffects[slot].arg.unk_09   = 0x10;
        g_BattleEffects[slot].target.party = work;
        g_Task->param.unk_0B               = g_Task->param.unk_0B + 1;
    }
    SND_QueueSelectionFx(0x100);
    g_Task->header.mode = g_Task->header.mode + 1;
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EED98(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EEDDC(void) {
    SYS_DISPATCH_BYTE(D_801F02B4, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF458();
        PopMatrix();
    }
}

MATCH void func_801EEE64(void) {
    g_Task->pos.x.fixed  = g_BattleSelectedActor->pos.x.fixed - 0x4000;
    g_Task->pos.y.fixed  = g_BattleSelectedActor->pos.y.fixed - 0x4000;
    g_Task->pos.z.fixed  = g_BattleSelectedActor->pos.z.fixed + 0x04000000;
    g_Task->param.unk_0B = 0x10;
    g_Task->unk_09       = 0x10;
    g_Task->timer        = 176;
    g_Task->header.step++;
}

MATCH void func_801EEEE4(void) {
    PartyMember* work = g_Task;
    u8           timer;

    work->pos.z.part.integer -= 0x40;

    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    if (timer == 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EEF34(void) {
    u8 count;
    u8 value;

    count = g_Task->unk_09;
    if ((count & BYTE_MASK) != 0x20) {
        g_Task->unk_09 = count + 1;
    }
    value         = g_Task->timer - 1;
    g_Task->timer = value;
    if ((value & BYTE_MASK) == 0x30) {
        g_Task->unk_09 = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EEFB8(void) {
    u8 count;
    u8 timer_next;

    count = g_Task->unk_09;
    if ((count & BYTE_MASK) != 0x20) {
        g_Task->unk_09 = count + 1;
    }
    timer_next    = g_Task->timer - 1;
    g_Task->timer = timer_next;
    if ((timer_next & BYTE_MASK) == 16) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF048(void) {
    PartyMember* work;

    work               = g_Task;
    work->timer        = work->timer - 1;
    work               = g_Task;
    work->param.unk_0B = work->param.unk_0B - 1;
    if (work->param.unk_0B == 0) {
        func_801E5988();
    }
}

MATCH void func_801EF0A8(void) {
    SYS_DISPATCH_BYTE(D_801F02C8, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF458();
        PopMatrix();
    }
}

MATCH void func_801EF130(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->pos.x.fixed  = D_8014637C->pos.x.fixed - 0x4000;
        g_Task->pos.y.fixed  = D_8014637C->pos.y.fixed - 0x4000;
        g_Task->pos.z.fixed  = D_8014637C->pos.z.fixed + 0x04000000;
        g_Task->param.unk_0B = 0x10;
        g_Task->unk_09       = 0x10;
        g_Task->timer        = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF1DC(void) {
    PartyMember* work;
    u8           timer;

    work  = g_Task;
    timer = work->unk_09 - 1;
    COORD_INT(work->pos.z) -= 0x40;
    work->unk_09 = timer;
    if (timer == 0) {
        g_Task->unk_09      = 0x20;
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EF23C(void) {
    u8 count;
    u8 value;

    count = g_Task->unk_09;
    if (count != 0) {
        g_Task->unk_09 = count - 1;
    }
    value         = g_Task->timer + 1;
    g_Task->timer = value;
    if ((value & BYTE_MASK) == 0x80) {
        g_Task->unk_09 = 0x20;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF2BC(void) {
    u8 count;
    u8 timer_next;

    count = g_Task->unk_09;
    if (count != 0) {
        g_Task->unk_09 = count - 1;
    }
    timer_next    = g_Task->timer + 1;
    g_Task->timer = timer_next;
    if ((timer_next & BYTE_MASK) == 160) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF348(void) {
    PartyMember* work;

    work               = g_Task;
    work->timer        = work->timer + 1;
    work               = g_Task;
    work->param.unk_0B = work->param.unk_0B - 1;
    if (work->param.unk_0B == 0) {
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF458);

MATCH void func_801EFBEC(void) {
    SYS_DISPATCH_BYTE(D_801F035C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801F002C();
        PopMatrix();
    }
}

MATCH void func_801EFC74(void) {
    PartyMember* src;

    src                 = g_Battle.selected_actor;
    g_Task->pos.x.fixed = src->pos.x.fixed;
    g_Task->pos.y.fixed = src->pos.y.fixed;
    g_Task->pos.z       = src->pos.z;
    g_Task->unk_09      = 4;
    g_Task->timer       = 176;
    g_Task->header.step = g_Task->header.step + 1;
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

MATCH void func_801EFD2C(void) {
    g_Task->timer -= 1;
    if (g_BattleEffectBattler->param.unk_0B == g_Task->header.mode) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFD84(void) {
    PartyMember* work;
    PartyMember* active;

    work         = g_Task;
    work->timer  = work->timer - 1;
    work         = g_Task;
    work->unk_09 = work->unk_09 - 1;
    if (work->unk_09 == 4) {
        active               = BATTLE_ACTIVE_WORK;
        active->param.unk_0B = active->param.unk_0B - 1;
        func_801E5988();
    }
}

MATCH void func_801EFE00(void) {
    SYS_DISPATCH_BYTE(D_801F036C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801F002C();
        PopMatrix();
    }
}

MATCH void func_801EFE88(void) {
    PartyMember* src;
    u8           timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        src                 = D_8014637C;
        g_Task->pos.x.fixed = src->pos.x.fixed;
        g_Task->pos.y.fixed = src->pos.y.fixed;
        g_Task->pos.z       = src->pos.z;
        g_Task->unk_09      = 4;
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void Effect_CountUpAndStep2(void) {
    BMAGIC_COUNT_UP_AND_STEP();
}

MATCH void func_801EFF58(void) {
    g_Task->timer += 1;
    if (g_BattleEffectBattler->param.unk_0B == g_Task->header.mode) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFFB0(void) {
    PartyMember* work;
    PartyMember* active;

    work         = g_Task;
    work->timer  = work->timer + 1;
    work         = g_Task;
    work->unk_09 = work->unk_09 - 1;
    if (work->unk_09 == 4) {
        active               = BATTLE_ACTIVE_WORK;
        active->param.unk_0B = active->param.unk_0B - 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F002C);
