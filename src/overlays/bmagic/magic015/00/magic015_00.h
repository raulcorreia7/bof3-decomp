#ifndef OVERLAY_BMAGIC_MAGIC015_00_H
#define OVERLAY_BMAGIC_MAGIC015_00_H

/* The bmagic/magic015/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BattleHandlerTable4 D_801EEC04;

extern BattleHandlerTable4 D_801EEC14;
extern BattleHandlerTable4 D_801EEC24;
extern BattleHandlerTable5 D_801EEC54;
extern u8                  g_BattleActiveBattler;

/* Fades the tint down to -0x80, then once the effect battler's param is 1 and the
 * fade is done, moves the effect onto that battler and advances. One body shared
 * by func_801F0A94 and func_801F1088; every change must verify both. Needs a local
 * `s8 tint`. */
#define EFFECT_APPEAR_AT_BATTLER()                                                                                 \
    tint = (s8)g_Task->unk_5D;                                                                                     \
    if (tint != -0x80) {                                                                                           \
        g_Task->unk_5D = tint - 0x10;                                                                              \
        g_Task->unk_5E -= 0x10;                                                                                    \
        g_Task->unk_5F -= 0x10;                                                                                    \
    }                                                                                                              \
    if ((g_BattleEffectBattler->param.unk_0B == 1) && ((s8)g_Task->unk_5D == -0x80) && (func_8014DAEC() & 0xFF)) { \
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;                                                  \
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;                                                  \
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;                                                  \
        g_Task->header.step++;                                                                                     \
    }

#endif
