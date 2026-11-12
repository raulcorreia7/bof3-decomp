#include "magic093_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_RunSlotsWithSetup.h"

INCLUDE_ASM(func_801EED04);

/* Starts the effect once bytes 0x09 and 0x0B of the work record are both zero. */
MATCH void func_801EF02C(void) {
    u16* flags;

    if ((PARTY_MEMBER_WORD_08(g_Task) & 0xFF00FF00u) == 0) {
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
        func_801E5988();
    }
}

/* func_801EF080 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF0C4(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 1), 2, g_Task);
}

INCLUDE_ASM(func_801EF108);

MATCH void func_801EF264(void) {
    if (g_BattleEffectBattler->param.unk_0B < 8U) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            Battle_MarkDamaged((g_Task->unk_03 + 3) & BYTE_MASK);
            GFX_FreePaletteFadeTarget(&g_BattleEnemyBattlers[g_Task->unk_03]);
            func_800AF814((g_Task->unk_03 + 3) & BYTE_MASK);
        } else {
            Battle_MarkDamaged(g_Task->unk_03);
            GFX_FreePaletteFadeTarget((EnemyBattler*)&g_Game.members[g_Task->unk_03]);
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
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 4), 1, g_Task);
}

MATCH void func_801EF41C(void) {
    SYS_DISPATCH_BYTE((g_BMagicEffectModes + 6), g_Task->header.step);
    g_Task->param.unk_0B += 1;
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF85C();
        func_801EFAE8();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF4C8);

INCLUDE_ASM(func_801EF600);

MATCH void func_801EF710(void) {
    PartyMember* active;
    PartyMember* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->param.unk_0B == 8) {
        work              = g_Task;
        work->header.step = work->header.step + 1;
    }
}

MATCH void func_801EF750(void) {
    PartyMember* work;

    work         = g_Task;
    work->unk_09 = work->unk_09 - 1;
    if (work->unk_09 == 0) {
        work               = (PartyMember*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        Actor_Clear();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF85C);

INCLUDE_ASM(func_801EFAE8);

MATCH void func_801EFE5C(void) {
    SYS_DISPATCH_BYTE(D_801F08C4, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
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
    PartyMember* work;

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
    u8 ticks;

    g_Task->unk_09 += 1;
    g_Task->timer -= 1;
    ticks                = g_Task->param.unk_0B - 1;
    g_Task->param.unk_0B = ticks;
    if (!(ticks & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801F01F0);

/* func_801F05BC */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0620 */
#include "overlays/bmagic/Actor_Clear.h"

INCLUDE_ASM(func_801F0670);
