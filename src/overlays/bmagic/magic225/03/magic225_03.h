#ifndef OVERLAY_BMAGIC_MAGIC225_03_H
#define OVERLAY_BMAGIC_MAGIC225_03_H

/* The bmagic/magic225/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"
#include "overlays/battle/battle/15/battle_15.h"

/* The handlers of the task by header.mode, copied onto the stack by value as retail does. */
#define BMAGIC_TEMPTATION_MODE_COUNT 4

typedef struct BMagicTemptationModes {
    Callback modes[BMAGIC_TEMPTATION_MODE_COUNT];
} BMagicTemptationModes;

extern s32                   D_1F80000C;
/* D_801EEC04 */
extern BMagicTemptationModes g_BMagicTemptationModes;
/* The scratchpad base as words: BMagic_TemptationDrawGlow stages its two radii and its shade there. */
extern s32                   D_1F800000_WORD[];
/* D_801F038C */
extern u8                    g_BMagicTemptationGlowColors[][3];
/* D_801F0398 */
extern Callback              g_BMagicTemptationFlashSteps[];
/* D_801F03AC */
extern Callback              g_BMagicTemptationActorSteps[];
/* D_801F03BC: the effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect          g_BMagicTemptationActors[];
#define BMAGIC_EFFECT_SLOTS g_BMagicTemptationActors
#define BMAGIC_EFFECT_COUNT 32

/* func_801EF7D4 */
void BMagic_TemptationDrawGlow(s32 x, s32 y, s32 radius, s32 color);

/* Mark the target and every unblocked battler on the selected side with MARK:
 * party slots below BATTLE_PARTY_CHARACTERS_COUNT, enemy rows from it. A statement
 * macro: the member declares s32 i. */
#define BMAGIC_MARK_SELECTED_SIDE(MARK)                                                                 \
    g_BattleActiveActor->unk_29 = (MARK);                                                               \
    i                           = 0;                                                                    \
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {                                          \
        do {                                                                                            \
            if (!(Battle_SlotIsBlocked((i + BATTLE_PARTY_CHARACTERS_COUNT) & BYTE_MASK) & BYTE_MASK)) { \
                g_BattleEnemyBattlers[i & BYTE_MASK].unk_29 = (MARK);                                   \
            }                                                                                           \
            i++;                                                                                        \
        } while ((u32)(i & BYTE_MASK) < 8);                                                             \
    } else {                                                                                            \
        do {                                                                                            \
            if (!(Battle_SlotIsBlocked(i & BYTE_MASK) & BYTE_MASK)) {                                   \
                g_Game.members[i & BYTE_MASK].unk_29 = (MARK);                                          \
            }                                                                                           \
            i++;                                                                                        \
        } while ((u32)(i & BYTE_MASK) < BATTLE_PARTY_CHARACTERS_COUNT);                                 \
    }

#endif
