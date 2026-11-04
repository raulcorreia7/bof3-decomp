#include "magic093_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EED04);

/* Matches (84 bytes) as: if the u32 at +0x08 masked with 0xFF00FF00 is zero,
 * BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING) and func_801E5988(); the u32 view is a cast.
 * needs: type PartyBattler+0x08 4 (3 sites: magic091 func_801EEEA8 with mask 0xFFFF0000, magic055
 * func_801EEEA8, this one). A union over unk_08..unk_0B renames about 940 lines in 240 files of the battle,
 * bmagic and boss overlays, so it waits for a round where no lane edits them. */
INCLUDE_ASM(func_801EF02C);

MATCH void func_801EF080(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF0C4(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 1), 2, g_SpadWork);
}

INCLUDE_ASM(func_801EF108);

INCLUDE_ASM(func_801EF264);

MATCH void func_801EF3A4(void) {
    BATTLE_ACTIVE_WORK->word_08.byte.unk_09--;
    func_801E5988();
}

MATCH void func_801EF3D8(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 4), 1, g_SpadWork);
}

INCLUDE_ASM(func_801EF41C);

INCLUDE_ASM(func_801EF4C8);

INCLUDE_ASM(func_801EF600);

MATCH void func_801EF710(void) {
    PartyBattler* active;
    PartyBattler* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->word_08.byte.unk_0B == 8) {
        work         = SP_REF(PartyBattler*, 0x44u);
        work->unk_02 = work->unk_02 + 1;
    }
}

MATCH void func_801EF750(void) {
    PartyBattler* work;

    work                      = g_SpadWork;
    work->word_08.byte.unk_09 = work->word_08.byte.unk_09 - 1;
    if (work->word_08.byte.unk_09 == 0) {
        work                      = (PartyBattler*)D_801EB4E0;
        work->word_08.byte.unk_0B = work->word_08.byte.unk_0B - 1;
        Actor_Clear();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF85C);

INCLUDE_ASM(func_801EFAE8);

MATCH void func_801EFE5C(void) {
    SYS_DISPATCH_BYTE(D_801F08C4, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_800AF764();
        func_801F01F0();
    }
}

INCLUDE_ASM(func_801EFEDC);

MATCH void func_801F00A0(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 + 32;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 192) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

MATCH void func_801F00F0(void) {
    PartyBattler* work;

    work = g_SpadWork;
    work->word_08.byte.unk_09 += 2;
    work = g_SpadWork;
    work->word_08.byte.unk_0A--;
    if (work->word_08.byte.unk_0A == 48) {
        work = g_SpadWork;
        work->unk_02++;
    }
}

INCLUDE_ASM(func_801F015C);

INCLUDE_ASM(func_801F01F0);

/* func_801F05BC */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0620 */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}

INCLUDE_ASM(func_801F0670);
