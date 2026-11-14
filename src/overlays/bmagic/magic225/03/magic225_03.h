#ifndef OVERLAY_BMAGIC_MAGIC225_03_H
#define OVERLAY_BMAGIC_MAGIC225_03_H

/* The bmagic/magic225/03 overlay. Only this image includes the file. */

#define BATTLE_PARTY_CELL_RECORD

#include "overlays/bmagic/bmagic.h"
#include "overlays/battle/battle/15/battle_15.h"

/* The step table the effect handler copies onto its stack by value, as retail does. */
typedef struct Magic225Steps {
    void (*steps[4])(void);
} Magic225Steps;

extern Magic225Steps D_801EEC04;
extern s32           D_1F80000C;
/* The scratchpad base as words: func_801EF7D4 stages its two radii and its shade there. */
extern s32           D_1F800000_WORD[];
/* The RGB of each of the four corner glows func_801EF7D4 draws. */
extern u8            D_801F038C[][3];
extern Callback      D_801F0398[];
extern Callback      D_801F03AC[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect  D_801F03BC[];
#define BMAGIC_EFFECT_SLOTS D_801F03BC
#define BMAGIC_EFFECT_COUNT 32

void func_801EF7D4(s32 x, s32 y, s32 radius, s32 color);

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
