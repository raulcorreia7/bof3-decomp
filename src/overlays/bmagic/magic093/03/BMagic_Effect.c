#include "magic093_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EED04);

/* Starts the effect once bytes 0x09 and 0x0B of the work record are both zero. */
MATCH void func_801EF02C(void) {
    u16* flags;

    if ((PARTY_BATTLER_WORD_08(g_Task) & 0xFF00FF00u) == 0) {
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
        func_801E5988();
    }
}

MATCH void func_801EF080(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->header.mode);
}

MATCH void func_801EF0C4(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 1), 2, g_Task);
}

INCLUDE_ASM(func_801EF108);

MATCH void func_801EF264(void) {
    if (D_801EB4E0->unk_0B < 8U) {
        if (g_BattleTargetSelector & BATTLE_TARGET_ENEMY_SIDE) {
            func_800A9820((g_Task->unk_03 + 3) & 0xFF);
            GFX_FreePaletteFadeTarget(&g_BattleEnemyBattlers[g_Task->unk_03]);
            func_800AF814((g_Task->unk_03 + 3) & 0xFF);
        } else {
            func_800A9820(g_Task->unk_03);
            GFX_FreePaletteFadeTarget((EnemyBattler*)&g_BattlePartyBattlers[g_Task->unk_03]);
            func_800AF814(g_Task->unk_03);
        }
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF3A4(void) {
    BATTLE_ACTIVE_WORK->unk_09--;
    func_801E5988();
}

MATCH void func_801EF3D8(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 4), 1, g_Task);
}

INCLUDE_ASM(func_801EF41C);

INCLUDE_ASM(func_801EF4C8);

INCLUDE_ASM(func_801EF600);

MATCH void func_801EF710(void) {
    PartyBattler* active;
    PartyBattler* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->unk_0B == 8) {
        work              = g_Task;
        work->header.step = work->header.step + 1;
    }
}

MATCH void func_801EF750(void) {
    PartyBattler* work;

    work         = g_Task;
    work->unk_09 = work->unk_09 - 1;
    if (work->unk_09 == 0) {
        work         = (PartyBattler*)D_801EB4E0;
        work->unk_0B = work->unk_0B - 1;
        Actor_Clear();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF85C);

INCLUDE_ASM(func_801EFAE8);

MATCH void func_801EFE5C(void) {
    SYS_DISPATCH_BYTE(D_801F08C4, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_800AF764();
        func_801F01F0();
    }
}

INCLUDE_ASM(func_801EFEDC);

MATCH void func_801F00A0(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 32;
    g_Task->unk_09 = timer;
    if (timer == 192) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F00F0(void) {
    PartyBattler* work;

    work = g_Task;
    work->unk_09 += 2;
    work = g_Task;
    work->timer--;
    if (work->timer == 48) {
        work = g_Task;
        work->header.step++;
    }
}

MATCH void func_801F015C(void) {
    u8 temp_v0;

    g_Task->unk_09 += 1;
    g_Task->timer -= 1;
    temp_v0        = g_Task->unk_0B - 1;
    g_Task->unk_0B = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        D_801EB4E0->unk_0B -= 1;
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801F01F0);

/* func_801F05BC */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0620 */
MATCH void Actor_Clear(void) {
    BMagic_ResetLocalWork();
}

INCLUDE_ASM(func_801F0670);
