#include "magic097_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    BMagic_DispatchTaskPair(func_801EEC5C, func_801EEF38);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EEF84(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->header.mode);
}

INCLUDE_ASM(func_801EEFC8);

#include "../../Effect_CountDownAndPickRandom.h"

INCLUDE_ASM(func_801EF1A4);

MATCH void func_801EF324(void) {
    u8 temp_v0;

    g_Task->unk_0B += 1;
    temp_v0        = g_Task->unk_09 - 1;
    g_Task->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
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

#include "overlays/bmagic/Effect_CountDownByTwoAndFinish.h"

#include "overlays/bmagic/Effect_SetActorMatrixRolled.h"

INCLUDE_ASM(func_801EF5C4);

INCLUDE_ASM(func_801EFE04);

/* blocker: frame 64 bytes against 56; first diff: addiu sp at +0x0. */
INCLUDE_ASM(func_801F0568);

INCLUDE_ASM(func_801F083C);
