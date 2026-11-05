#include "magic056_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC94);

INCLUDE_ASM(func_801EEF3C);

#include "shared/Effect_StartPlaying.h"

MATCH void func_801EF1B0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

MATCH void func_801EF1F4(void) {
    SYS_DISPATCH_BYTE(D_801F0754, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 0) {
        Effect_SetActorMatrix();
        func_801EF4C0();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CopyBattlerCoords.h"

MATCH void func_801EF2DC(void) {
    u8 counter;

    if (g_Task->unk_09 == 4) {
        func_800A9610(g_BattleTargetSelector, 0x10U);
    }
    SP_REF(s16, 0) = g_Task->unk_09 * 0x1C;
    counter        = g_Task->unk_09 + 1;
    g_Task->unk_09 = counter;
    if ((counter & 0xFF) == 0xC) {
        g_Task->step += 1;
    }
}

MATCH void func_801EF37C(void) {
    u8 temp_v0;

    SP_REF(s16, 0u) = (g_Task->unk_09 * 4) + 0x120;
    g_Task->timer += 1;
    temp_v0        = g_Task->unk_09 + 1;
    g_Task->unk_09 = temp_v0;
    if ((temp_v0 & 0xFF) == 0x28) {
        D_801EB4E0->unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF4C0);

MATCH void func_801EFA50(void) {
    SYS_DISPATCH_BYTE(D_801F0760, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 0) {
        Effect_SetActorMatrix();
        func_801EFC74();
        PopMatrix();
    }
}

MATCH void Effect_CopyBattlerCoords_801EFAD8(void) {
    PartyBattler* src;

    BMAGIC_COPY_BATTLER_COORDS();
}

MATCH void func_801EFB38(void) {
    PartyBattler* work;

    work = g_Task;
    work->timer += 2;
    work = g_Task;
    work->unk_09++;
    if (work->unk_09 == 12) {
        work = g_Task;
        work->step++;
    }
}

#include "overlays/bmagic/Effect_CountUpAndStepAt30.h"

#include "overlays/bmagic/Effect_CountDownTimerCapped.h"

INCLUDE_ASM(func_801EFC74);

INCLUDE_ASM(func_801EFF28);

MATCH void func_801EFFE8(void) {
    g_Task->unk_27 = BATTLE_ACTIVE_WORK->unk_27;
    g_Task->step++;
}

#include "overlays/bmagic/Effect_PrimeTintOnScriptReady.h"

MATCH void func_801F00C8(void) {
    PartyBattler* work;
    PartyBattler* source;

    g_Task->unk_5D -= 0x10;
    g_Task->unk_5E -= 0x10;
    g_Task->unk_5F -= 0x10;
    if ((s8)g_Task->unk_5D == -0x80) {
        work              = g_Task;
        source            = BATTLE_ACTIVE_WORK;
        work->pos.x.fixed = source->pos.x.fixed;
        work->pos.y.fixed = source->pos.y.fixed;
        work->pos.z.fixed = source->pos.z.fixed;
        work->step += 1;
    }
}

MATCH void func_801F0178(void) {
    g_Task->unk_5D += 0x10;
    g_Task->unk_5E += 0x10;
    g_Task->unk_5F += 0x10;
    if ((s8)g_Task->unk_5D == 0) {
        g_Task->flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
        g_Task->unk_5C = 0;
        g_Task->unk_09 = 8;
        g_Task->step += 1;
    }
}

INCLUDE_ASM(func_801F023C);

MATCH void func_801F042C(void) {
    u8 count;

    func_8014D978();
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & 0xFF)) {
        g_Task->flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        g_Task->unk_5C = 1;
        g_Task->unk_5D = 0;
        g_Task->unk_5E = 0;
        g_Task->unk_5F = 0;
        g_Task->step += 1;
    }
}

INCLUDE_ASM(func_801F04EC);

MATCH void func_801F0658(void) {
    if (D_801EB4E0->unk_0B == 1) {
        g_Task->unk_5D += 0x10;
        g_Task->unk_5E += 0x10;
        g_Task->unk_5F += 0x10;
        if ((s8)g_Task->unk_5D == 0) {
            D_801EB4E0->unk_0B -= 1;
            g_Task->step += 1;
        }
    }
}

MATCH void func_801F0724(void) {
    func_801E5988();
}
