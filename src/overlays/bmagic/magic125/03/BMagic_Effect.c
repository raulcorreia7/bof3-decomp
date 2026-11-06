#include "magic125_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EED04);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEEC0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, TASK_BYTES[1]);
}

INCLUDE_ASM(func_801EEF04);

MATCH void func_801EEFF8(void) {
    u8 count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & 0xFF)) {
        g_Task->pos.x.fixed = D_801EB4E0->pos.x.fixed;
        g_Task->pos.y.fixed = D_801EB4E0->pos.y.fixed;
        g_Task->pos.z.fixed = D_801EB4E0->pos.z.fixed + 0x04000000;
        g_Task->unk_5D      = (rand() & 3) + 4;
        g_Task->unk_5E      = (rand() & 3) + 4;
        g_Task->unk_5F      = (rand() & 3) + 4;
        g_Task->unk_14      = 0x100;
        g_Task->unk_09      = 0x10;
        g_Task->timer       = 8;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF0F8(void) {
    PartyBattler* work  = g_Task;
    u8            timer = work->timer - 1;
    work->timer         = timer;
    work->pos.z.fixed += 0xFF800000;
    if (timer == 0) {
        g_Task->header.step += 1;
    }
}

/* Best 7 differences: lui a0 at 0x801EF148; adjust register allocation. */
/* blocker: work pointer register; first diff: lui v0 at entry. */
INCLUDE_ASM(func_801EF148);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF258);

INCLUDE_ASM(func_801EF508);

MATCH void func_801EF808(void) {
    SYS_DISPATCH_BYTE(D_801F05EC, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF508();
        PopMatrix();
    }
}

MATCH void func_801EF890(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & 0xFF)) {
        g_Task->pos.x.fixed = D_801EB4E0->pos.x.fixed;
        g_Task->pos.y.fixed = D_801EB4E0->pos.y.fixed;
        g_Task->pos.z.fixed = D_801EB4E0->pos.z.fixed;
        g_Task->unk_5D      = 0xF;
        g_Task->unk_5E      = 0xF;
        g_Task->unk_5F      = 0xF;
        g_Task->unk_14      = 0x100;
        g_Task->unk_20      = 0x21;
        g_Task->unk_09      = 0x10;
        g_Task->timer       = 0x1E;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF960);

MATCH void func_801EFAB0(void) {
    s32 level;
    u8  counter;

    level = g_Task->unk_14;
    if (level >= 9) {
        g_Task->unk_14 = level - 1;
    }
    if (g_FrameCount & 1) {
        counter        = g_Task->unk_09 - 1;
        g_Task->unk_09 = counter;
        if (!(counter & 0xFF)) {
            BATTLE_ACTIVE_WORK->unk_0B -= 1;
            func_801E5988();
        }
    }
}

MATCH void func_801EFB48(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 8), 1, g_Task);
}

INCLUDE_ASM(func_801EFB8C);

INCLUDE_ASM(func_801EFCE4);

INCLUDE_ASM(func_801EFE8C);

INCLUDE_ASM(func_801EFFC8);

INCLUDE_ASM(func_801F020C);

/* func_801F0524 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0588 */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}
