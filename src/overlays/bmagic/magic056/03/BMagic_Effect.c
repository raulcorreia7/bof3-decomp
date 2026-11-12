/* Every position copy re-reads the party cell. */
#define BATTLE_PARTY_CELL_RECORD_VOLATILE
#include "magic056_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC94);

INCLUDE_ASM(func_801EEF3C);

#include "shared/Effect_StartPlaying.h"

/* func_801EF1B0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF1F4(void) {
    SYS_DISPATCH_BYTE(D_801F0754, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF4C0();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CopyBattlerCoords.h"

MATCH void func_801EF2DC(void) {
    u8 counter;

    if (g_Task->unk_09 == 4) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
    }
    SP_REF(s16, 0) = g_Task->unk_09 * 0x1C;
    counter        = g_Task->unk_09 + 1;
    g_Task->unk_09 = counter;
    if ((counter & BYTE_MASK) == 0xC) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF37C(void) {
    u8 count;

    SP_REF(s16, 0u) = (g_Task->unk_09 * 4) + 0x120;
    g_Task->timer += 1;
    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x28) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF4C0);

MATCH void func_801EFA50(void) {
    SYS_DISPATCH_BYTE(D_801F0760, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EFC74();
        PopMatrix();
    }
}

MATCH void Effect_CopyBattlerCoords2(void) {
    BMAGIC_COPY_BATTLER_COORDS();
}

MATCH void func_801EFB38(void) {
    PartyMember* work;

    work = g_Task;
    work->timer += 2;
    work = g_Task;
    work->unk_09++;
    if (work->unk_09 == 12) {
        work = g_Task;
        work->header.step++;
    }
}

#include "overlays/bmagic/Effect_CountUpAndStepAt30.h"

#include "overlays/bmagic/Effect_CountDownTimerCapped.h"

INCLUDE_ASM(func_801EFC74);

MATCH void func_801EFF28(void) {
    Magic056Steps handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
}

MATCH void func_801EFFE8(void) {
    g_Task->unk_27 = BATTLE_ACTIVE_WORK->unk_27;
    g_Task->header.step++;
}

#include "overlays/bmagic/Effect_PrimeTintOnScriptReady.h"

MATCH void func_801F00C8(void) {
    PartyMember* work;
    PartyMember* source;

    g_Task->unk_5D -= 16;
    g_Task->unk_5E -= 16;
    g_Task->unk_5F -= 16;
    if ((s8)g_Task->unk_5D == -128) {
        work   = g_Task;
        source = BATTLE_ACTIVE_WORK;
        WorldPos_Copy(&work->pos, &source->pos);
        work->header.step += 1;
    }
}

MATCH void func_801F0178(void) {
    g_Task->unk_5D += 0x10;
    g_Task->unk_5E += 0x10;
    g_Task->unk_5F += 0x10;
    if ((s8)g_Task->unk_5D == 0) {
        g_Task->header.flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
        g_Task->unk_5C = 0;
        g_Task->unk_09 = 8;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801F023C);

MATCH void func_801F042C(void) {
    u8 count;

    Actor_StepAnimLoop();
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        g_Task->unk_5C = 1;
        g_Task->unk_5D = 0;
        g_Task->unk_5E = 0;
        g_Task->unk_5F = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F04EC(void) {
    PartyMember* member;
    PartyMember* work;

    Actor_StepAnimLoop();
    g_Task->unk_5D -= 0x10;
    g_Task->unk_5E -= 0x10;
    g_Task->unk_5F -= 0x10;
    if ((s8)g_Task->unk_5D == -0x80) {
        work              = g_Task;
        work->pos.x.fixed = D_8014637C->pos.x.fixed;
        /* FAKE: retail schedules each copy's load and store together. */
        FAKE_ORDER_FENCE();
        work->pos.y.fixed = D_8014637C->pos.y.fixed;
        /* FAKE: retail schedules each copy's load and store together. */
        FAKE_ORDER_FENCE();
        work->pos.z.fixed = D_8014637C->pos.z.fixed;
        if (g_Battle.active_battler < 3) {
            member = &g_Game.members[g_Battle.active_battler];
            g_Task = member;
            Actor_SelectScript(member->facing + 0x1C);
            g_Task = work;
            Actor_SelectScript(work->facing + 0x1C);
        } else {
            func_801E257C(g_Battle.active_battler, 4);
        }
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0658(void) {
    if (g_BattleEffectBattler->param.unk_0B == 1) {
        g_Task->unk_5D += 0x10;
        g_Task->unk_5E += 0x10;
        g_Task->unk_5F += 0x10;
        if ((s8)g_Task->unk_5D == 0) {
            g_BattleEffectBattler->param.unk_0B -= 1;
            g_Task->header.step += 1;
        }
    }
}

MATCH void func_801F0724(void) {
    func_801E5988();
}
