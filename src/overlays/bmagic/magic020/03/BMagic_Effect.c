#include "magic020_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_DispatchMode.h"

INCLUDE_ASM(func_801EECC0);

INCLUDE_ASM(func_801EF0F8);

MATCH void func_801EF234(void) {
    u8 timer;

    func_801EFD88();
    if (g_Task->param.unk_0B == 0) {
        timer          = g_Task->unk_09 - 1;
        g_Task->unk_09 = timer;
        if (timer == 0) {
            g_Task->header.mode = g_Task->header.mode + 1;
        }
    }
}

MATCH void func_801EF2A8(void) {
    if (g_Task->param.unk_0B == 0xFF) {
        func_800AFC54();
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        func_800AEF98(4, 0);
        g_Task->header.mode += 1;
    }
}

#include "shared/Effect_StartPlaying.h"

#include "shared/Effect_PlayOnce.h"

/* func_801EF398 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF3DC(void) {
    Magic020Steps handlers = D_801EEC1C;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
}

MATCH void func_801EF498(void) {
    PartyMember* work;
    s32          z;

    g_Task->unk_27    = g_BattleEffectBattler->unk_27;
    g_Task->unk_2B    = 1;
    work              = g_Task;
    work->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    work->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    z                 = g_BattleEffectBattler->pos.z.fixed;
    work->unk_09      = 0x10;
    work->pos.z.fixed = z;
    g_Task->header.step++;
}

MATCH void func_801EF518(void) {
    PartyMember** selected;

    selected = &g_Battle.selected_actor;
    func_800AF2B4(*selected, 0x60);
    if (func_800AF66C(*selected, 0x20000)) {
        g_Task->unk_09                   = func_800AFF98();
        BATTLE_ACTIVE_WORK->param.unk_0B = 0xFF;
        g_Task->header.step++;
    }
}

MATCH void func_801EF5A4(void) {
    u8 timer;

    Actor_StepAnimOnce();
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EF608(void) {
    if ((BATTLE_ACTIVE_WORK->param.unk_0B == 0) && (Actor_StepAnimOnce() & BYTE_MASK)) {
        g_Task->unk_09 = 0x10;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF678(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        s8 tone;

        g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        g_Task->unk_5C = 1;
        tone           = -0x40;
        g_Task->unk_5D = tone;
        g_Task->unk_5E = tone;
        g_Task->unk_5F = tone;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF720(void) {
    PartyMember* work;
    PartyMember* source;

    g_Task->unk_5D -= 8;
    g_Task->unk_5E -= 8;
    g_Task->unk_5F -= 8;
    if ((s8)g_Task->unk_5D == -128) {
        work   = g_Task;
        source = BATTLE_ACTIVE_WORK;
        WorldPos_Copy(&work->pos, &source->pos);
        work->header.step += 1;
    }
}

MATCH void func_801EF7D0(void) {
    g_Task->unk_5D += 0x10;
    g_Task->unk_5E += 0x10;
    g_Task->unk_5F += 0x10;
    if ((s8)g_Task->unk_5D == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B = 0xFF;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF874(void) {
    func_801E5988();
}

MATCH void func_801EF894(void) {
    Magic020SecondSteps handlers;

    handlers = D_801EEC3C;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
}

MATCH void func_801EF928(void) {
    PartyMember* work;
    PartyMember* source;
    u8           count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        g_Task->unk_5C = 1;
        g_Task->unk_5D = -((g_Task->param.unk_0B + 1) * 20);
        g_Task->unk_5E = -((g_Task->param.unk_0B + 1) * 20);
        g_Task->unk_5F = -((g_Task->param.unk_0B + 1) * 20);
        g_Task->unk_2B = 0;
        g_Task->unk_27 = g_BattleEffectBattler->unk_27;
        work           = g_Task;
        source         = BATTLE_ACTIVE_WORK;
        WorldPos_Copy(&work->pos, &source->pos);
        work->header.step += 1;
    }
}

MATCH void func_801EFA70(void) {
    PartyMember** selected;

    selected = &g_Battle.selected_actor;
    func_800AF2B4(*selected, 0x60);
    if (func_800AF66C(*selected, 0x20000)) {
        g_Task->header.step++;
    }
}

MATCH void func_801EFAD4(void) {
    func_801E5988();
}

/* hint: a local Callback[2] of func_801EFBA0 and func_801EFD10 fails to compile at the first function-pointer store (handlers[0] = func_801EFBA0); not byte-compared. */
INCLUDE_ASM(func_801EFAF4);

INCLUDE_ASM(func_801EFBA0);

MATCH void func_801EFD10(void) {
    if (Actor_StepAnimLoop() & BYTE_MASK) {
        if (g_Task->param.unk_0B == 7) {
            func_800A9820(g_Battle.target_selector);
        }
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EFD88);
