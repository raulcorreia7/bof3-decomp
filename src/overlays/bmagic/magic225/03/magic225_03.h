#ifndef OVERLAY_BMAGIC_MAGIC225_03_H
#define OVERLAY_BMAGIC_MAGIC225_03_H

/* The bmagic/magic225/03 overlay. Only this image includes the file. */

#define BATTLE_PARTY_CELL_RECORD

#include "overlays/bmagic/bmagic.h"


/* The step table the effect handler copies onto its stack by value, as retail does. */
typedef struct Magic225Steps {
    void (*steps[4])(void);
} Magic225Steps;

extern Magic225Steps D_801EEC04;
extern Callback      D_801F0398[];
extern Callback      D_801F03AC[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect  D_801F03BC[];
#define BMAGIC_EFFECT_SLOTS D_801F03BC
#define BMAGIC_EFFECT_COUNT 32

/* Mark the target and every unblocked battler on the selected side with MARK:
 * party slots below BATTLE_PARTY_CHARACTERS_COUNT, enemy rows from it. A statement
 * macro: the member declares s32 i. */
#define BMAGIC_MARK_SELECTED_SIDE(MARK)                                                                 \
    D_8014637C->unk_29 = (MARK);                                                                        \
    i                  = 0;                                                                             \
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
