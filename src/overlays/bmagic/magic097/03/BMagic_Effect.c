#include "magic097_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Bmagic_DispatchTaskPair(func_801EEC5C, func_801EEF38);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EEF84(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

INCLUDE_ASM(func_801EEFC8);

#include "../../Effect_CountDownAndPickRandom.h"

INCLUDE_ASM(func_801EF1A4);

MATCH void func_801EF324(void) {
    u8 temp_v0;

    g_SpadWork->word_08.byte.unk_0B += 1;
    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        if (g_BattleTargetSelector & 0x40) {
            func_800A9820((g_SpadWork->unk_03 + 3) & 0xFF);
            func_80196718(&D_801EB630[g_SpadWork->unk_03]);
            func_800AF814((g_SpadWork->unk_03 + 3) & 0xFF);
        } else {
            func_800A9820(g_SpadWork->unk_03);
            func_80196718((EnemyBattler*)&g_BattlePartyBattlers[g_SpadWork->unk_03]);
            func_800AF814(g_SpadWork->unk_03);
        }
        g_SpadWork->unk_02 += 1;
    }
}

#include "overlays/bmagic/Effect_CountDownByTwoAndFinish.h"

#include "overlays/bmagic/Effect_SetActorMatrixRolled.h"

INCLUDE_ASM(func_801EF5C4);

INCLUDE_ASM(func_801EFE04);

/* Follows sce10eff func_801D218C (160 instructions) but draws through Area_AddCellPrim(x, y, 2, 12) with the vector
 * scaled by sra 3 into the call, so the frame is 64 bytes against 56 (first difference addiu sp at +0x0) */
INCLUDE_ASM(func_801F0568);

INCLUDE_ASM(func_801F083C);
