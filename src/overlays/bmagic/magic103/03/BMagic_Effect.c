#include "magic103_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC70);

#include "overlays/bmagic/Effect_Hit.h"

#include "shared/Effect_StartPlaying.h"

/* func_801EEEC8 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF0C(void) {
    SYS_DISPATCH_BYTE(D_801F07A0, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF1D8();
        PopMatrix();
    }
}

MATCH void func_801EEF94(void) {
    PartyMember* src;

    src                      = g_Battle.selected_actor;
    g_Task->pos.x.fixed      = src->pos.x.fixed;
    g_Task->pos.y.fixed      = src->pos.y.fixed;
    COORD_INT(g_Task->pos.z) = COORD_INT(src->pos.z);
    g_Task->unk_09           = 0;
    g_Task->timer            = 0;
    g_Task->header.step      = g_Task->header.step + 1;
}

MATCH void func_801EEFF4(void) {
    u8 counter;

    if (g_Task->unk_09 == 4) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
    }
    SP_REF(s16, 0) = g_Task->unk_09 * 0x1C;
    counter        = g_Task->unk_09 + 1;
    g_Task->unk_09 = counter;
    if ((counter & BYTE_MASK) == 0x8) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF094(void) {
    u8 count;

    SP_REF(s16, 0u) = (g_Task->unk_09 * 4) + 0xC0;
    g_Task->timer += 1;
    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x28) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF1D8);

INCLUDE_ASM(func_801EF7CC);

MATCH void func_801EFB10(void) {
    SYS_DISPATCH_BYTE(D_801F07C4, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EFE20();
    }
}

MATCH void func_801EFB88(void) {
    PartyMember* work;
    u8           timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        work              = g_Task;
        work->pos.x.fixed = g_BattleSelectedActor->pos.x.fixed + D_801F07AC[work->param.unk_0B].x;
        work->pos.y.fixed = g_BattleSelectedActor->pos.y.fixed + D_801F07AC[work->param.unk_0B].y;
        work->pos.z.fixed = g_BattleSelectedActor->pos.z.fixed + D_801F07AC[work->param.unk_0B].z;
        work->unk_09      = 0;
        g_Task->timer     = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFC70(void) {
    u8 count;

    Battle_ProjectRange();
    g_Task->timer += 2;
    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 8) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFCF4(void) {
    PartyMember* work;
    u8           counter;
    s32          drop;

    Battle_ProjectRange();
    work         = g_Task;
    counter      = work->unk_09 + 1;
    drop         = (VOL(u8, work->unk_09) - 8) / 2;
    work->unk_09 = counter;
    work->unk_30.half -= drop;
    if ((counter & BYTE_MASK) == 0x1C) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFD74(void) {
    u8 counter;

    Battle_ProjectRange();
    g_Task->unk_30.half -= (g_Task->unk_09 - 8) / 2;
    if ((g_Task->unk_09 & BYTE_MASK) != 0x2C) {
        g_Task->unk_09 = g_Task->unk_09 + 1;
    }
    counter       = g_Task->timer - 1;
    g_Task->timer = counter;
    if (!(counter & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EFE20);

MATCH void func_801F02BC(void) {
    SYS_DISPATCH_BYTE(D_801F07D4, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801F04E0();
        PopMatrix();
    }
}

MATCH void func_801F0344(void) {
    PartyMember* src;

    src                 = g_Battle.selected_actor;
    g_Task->pos.x.fixed = src->pos.x.fixed;
    g_Task->pos.y.fixed = src->pos.y.fixed;
    g_Task->pos.z       = src->pos.z;
    g_Task->unk_09      = 0;
    g_Task->timer       = 0;
    g_Task->header.step = g_Task->header.step + 1;
}

MATCH void func_801F03A4(void) {
    PartyMember* work;

    work = g_Task;
    work->timer += 2;
    work = g_Task;
    work->unk_09++;
    if (work->unk_09 == 8) {
        work = g_Task;
        work->header.step++;
    }
}

#include "overlays/bmagic/Effect_CountUpAndStepAt30.h"

#include "overlays/bmagic/Effect_CountDownTimerCapped.h"

INCLUDE_ASM(func_801F04E0);
