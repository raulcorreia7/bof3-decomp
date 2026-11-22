#include "magic098_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    BMagic_DispatchTaskPair(func_801EEC5C, func_801EEF38);
}

#include "overlays/bmagic/shared/BMagic_SpawnAtTargets.h"

MATCH void func_801EEC5C(void) {
    u32          i;
    u32          slot;
    PartyMember* work;

    BMAGIC_SPAWN_AT_TARGETS(14);
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

/* func_801EEF84 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFC8(void) {
    SYS_DISPATCH_BYTE((g_BMagicEffectModes + 1), TASK(PartyMember)->header.step);
    func_800AF764();
    if (TASK(PartyMember)->header.step != 0 && TASK(PartyMember)->header.flags != 0) {
        Effect_SetActorMatrixRolled();
        func_801EF5D4(24, 32, 3);
        TASK(PartyMember)->param.unk_0B += 8;
        func_801EF5D4(16, 80, 0xF);
        TASK(PartyMember)->param.unk_0B += 2;
        func_801EFE24();
        TASK(PartyMember)->param.unk_0B += 6;
        func_801EF5D4(16, 128, 0x1F);
        TASK(PartyMember)->param.unk_0B -= 16;
        TASK(PartyMember)->screen_x.value += 24;
        func_801F00C4();
        TASK(PartyMember)->screen_x.value -= 48;
        func_801F00C4();
        PopMatrix();
    }
}

#include "overlays/bmagic/shared/Effect_CountDownAndPickRandom.h"

/* Counts up and, at sixteen, swaps the target battler's palette fade for a
 * black one. */
MATCH void func_801EF1B4(void) {
    PartyMember* battler;

    TASK(PartyMember)->timer = TASK(PartyMember)->timer + 4;
    TASK(PartyMember)->param.unk_0B += 1;
    if (TASK(PartyMember)->timer == 16) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            battler = (PartyMember*)&g_BattleEnemyBattlers[TASK(PartyMember)->unk_03];
            GFX_PaletteFreeFadeTarget(battler);
            GFX_PaletteAllocFade(battler, -8, -8, -8, 1);
            func_800A9610((u8)(TASK(PartyMember)->unk_03 + 3), 0x10);
        } else {
            battler = &g_Game.members[TASK(PartyMember)->unk_03];
            GFX_PaletteFreeFadeTarget(battler);
            GFX_PaletteAllocFade(battler, -8, -8, -8, 1);
            func_800A9610(TASK(PartyMember)->unk_03, 0x10);
        }
        TASK(PartyMember)->unk_09 = 8;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801EF334 */
#include "overlays/bmagic/shared/Effect_ReleaseTarget.h"
