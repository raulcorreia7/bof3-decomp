#ifndef OVERLAY_BMAGIC_MAGIC220_03_H
#define OVERLAY_BMAGIC_MAGIC220_03_H

/* The bmagic/magic220/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern s16 D_1F800004;

extern Callback D_801F06E0[];
extern Callback D_801F0700[];

extern Callback     D_801F0704[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F0710[];
#define BMAGIC_EFFECT_SLOTS     D_801F0710
#define BMAGIC_EFFECT_COUNT     64
#define BMAGIC_EFFECT_SLOT_STEP func_801EFF60

/* Alternates the effect between both sides of the battler by unk_0C, then
 * every eighth frame queues the selection sound and spawns sixteen children
 * on the battler. A statement macro: the member declares PartyMember* battler,
 * u8 i and u8 slot. */
#define MAGIC220_SWAY_AND_SPAWN()                                                  \
    if (g_FrameCount & 0x1) {                                                      \
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + g_Task->unk_0C; \
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed - g_Task->unk_0C; \
    } else {                                                                       \
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed - g_Task->unk_0C; \
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + g_Task->unk_0C; \
    }                                                                              \
    if ((g_FrameCount & 0x7) == 0) {                                               \
        SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 2));                      \
        for (i = 0; i < 16; i++) {                                                 \
            slot = BMagic_AllocEffect();                                           \
            if (slot != GAME_NONE) {                                               \
                battler                                = g_BattleEffectBattler;    \
                BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;                        \
                BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;                        \
                BMAGIC_EFFECT_SLOTS[slot].target.party = battler;                  \
                g_BattleEffectBattler->param.unk_0B++;                             \
            }                                                                      \
        }                                                                          \
    }
extern Magic220SharedSteps D_801EEC04;
void                       func_801EFF60(void);
void                       func_801F0334(void);

#endif
