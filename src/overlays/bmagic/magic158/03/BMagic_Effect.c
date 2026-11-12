#include "magic158_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_RunSlotsWithSetup.h"

#include "overlays/bmagic/func_801EED04.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEEF0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF34(void) {
    SYS_DISPATCH_BYTE(D_801EF788, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF2F0();
        func_801EF3EC();
        PopMatrix();
    }
}

/* At the ticker's zero, places the effect half a cell from the battler by the
 * angle byte 0x0B and starts its rise from a random tint row. */
MATCH void func_801EEFBC(void) {
    u8   count;
    s32  phase;
    s32  entry;
    s16* angle_cell;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        angle_cell          = &D_1F800004;
        phase               = g_Task->param.unk_0B & 0xF;
        *angle_cell         = phase << 8;
        /* kept: (s16) types the rsin angle; without it GCC folds the two shifts and the body is 4 bytes short. */
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + ((rsin((s16)(phase << 8)) * 0x8000) >> 12);
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + ((rcos(*angle_cell) * 0x8000) >> 12);
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + TO_COORD(1152);
        entry               = RANDOM_MASK(7) * 3;
        g_Task->unk_5D      = D_801EF76C[entry];
        g_Task->unk_5E      = D_801EF76D[entry];
        g_Task->unk_5F      = D_801EF76E[entry];
        g_Task->unk_14      = 0x80;
        g_Task->unk_20      = -0x10;
        g_Task->unk_09      = 8;
        g_Task->timer       = 2;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF140(void) {
    u8 count;
    u8 timer;

    count                    = g_Task->unk_09;
    COORD_INT(g_Task->pos.z) = COORD_INT(g_Task->pos.z) - 0x60;
    if ((count & BYTE_MASK) != 0x10) {
        g_Task->unk_09 = count + 1;
    }
    timer = g_Task->timer;
    if (timer != 16) {
        g_Task->timer = timer + 2;
    }
    if (COORD_INT(g_Task->pos.z) == COORD_INT(BATTLE_ACTIVE_WORK->pos.z)) {
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF1C8);

#include "overlays/bmagic/BMagic_SetupEffectMatrix.h"

MATCH void func_801EF2F0(void) {
    BMAGIC_SETUP_EFFECT_MATRIX();
}

INCLUDE_ASM(func_801EF3EC);

/* func_801EF708 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
