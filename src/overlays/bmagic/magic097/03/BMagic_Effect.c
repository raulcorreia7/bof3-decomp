#include "magic097_03.h"

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

    BMAGIC_SPAWN_AT_TARGETS(20);
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

/* func_801EEF84 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFC8(void) {
    SYS_DISPATCH_BYTE((g_BMagicEffectModes + 1), BMAGIC_WORK->header.step);
    func_800AF764();
    if (BMAGIC_WORK->header.step != 0 && BMAGIC_WORK->header.flags != 0) {
        Effect_SetActorMatrixRolled();
        func_801EF5C4(MAGIC097_BAND_HEIGHT, 32, 0x7);
        BMAGIC_WORK->param.unk_0B += 4;
        func_801EF5C4(MAGIC097_BAND_HEIGHT, 64, 0xF);
        Effect_DrawBolt();
        BMAGIC_WORK->param.unk_0B += 4;
        func_801EF5C4(MAGIC097_BAND_HEIGHT, 96, 0x1F);
        Effect_DrawBolt();
        BMAGIC_WORK->param.unk_0B -= 8;
        BMAGIC_WORK->screen_x.value += 16;
        func_801F083C();
        BMAGIC_WORK->screen_x.value -= 32;
        func_801F083C();
        PopMatrix();
    }
}

#include "overlays/bmagic/shared/Effect_CountDownAndPickRandom.h"

MATCH void func_801EF1A4(void) {
    void* battler;

    BMAGIC_WORK->param.unk_0B += 1;
    BMAGIC_WORK->timer += 4;
    if (BMAGIC_WORK->timer == 0x10) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            battler = &g_BattleEnemyBattlers[BMAGIC_WORK->unk_03];
            GFX_PaletteFreeFadeTarget(battler);
            GFX_PaletteAllocFade(battler, -8, -8, -8, 1);
            Battle_ApplyDamageFlags((BMAGIC_WORK->unk_03 + 3) & BYTE_MASK, 0x10);
        } else {
            battler = &g_Game.members[BMAGIC_WORK->unk_03];
            GFX_PaletteFreeFadeTarget(battler);
            GFX_PaletteAllocFade(battler, -8, -8, -8, 1);
            Battle_ApplyDamageFlags(BMAGIC_WORK->unk_03, 0x10);
        }
        BMAGIC_WORK->unk_09 = 8;
        BMAGIC_WORK->header.step += 1;
    }
}

/* func_801EF324 */
