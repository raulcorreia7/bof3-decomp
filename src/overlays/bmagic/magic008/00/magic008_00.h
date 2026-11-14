#ifndef OVERLAY_BMAGIC_MAGIC008_00_H
#define OVERLAY_BMAGIC_MAGIC008_00_H

/* The bmagic/magic008/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

#define MAGIC008_EARLY_STEP_COUNT 7
#define MAGIC008_STEP_COUNT       10

typedef struct Magic008EarlySteps {
    Callback handlers[MAGIC008_EARLY_STEP_COUNT];
} Magic008EarlySteps;

typedef struct Magic008Steps {
    Callback handlers[MAGIC008_STEP_COUNT];
} Magic008Steps;

#define MAGIC008_FIRST_STEP_COUNT 4

typedef struct Magic008FirstSteps {
    Callback steps[MAGIC008_FIRST_STEP_COUNT];
} Magic008FirstSteps;

#define MAGIC008_SECOND_STEP_COUNT 3

typedef struct Magic008SecondSteps {
    Callback steps[MAGIC008_SECOND_STEP_COUNT];
} Magic008SecondSteps;

#define MAGIC008_THIRD_STEP_COUNT 5

typedef struct Magic008ThirdSteps {
    Callback steps[MAGIC008_THIRD_STEP_COUNT];
} Magic008ThirdSteps;

extern Magic008FirstSteps D_801EEC04;
extern BMagicEffectFuncs  D_801EEC58;

extern Magic008SecondSteps D_801EEC14;
extern Magic008ThirdSteps  D_801EEC70;
extern Magic008FirstSteps  D_801EEC20;
extern Magic008FirstSteps  D_801EEC30;
extern Magic008SecondSteps D_801EEC40;
extern Magic008SecondSteps D_801EEC4C;
extern Magic008FirstSteps  D_801EEC84;
extern BMagicEffectFuncs   D_801EEC94;

extern Magic008EarlySteps D_801EECAC;
extern Magic008Steps      D_801EECC8;
extern Point2DL           D_801F1C04[];
extern u8                 D_800B6BF0[];
u8                        func_800AED5C(s32 battler, u32 battler_index);
/* The battle/battle/15 sprite-cell routines, called with a battler or the effect work record. */
u32                       func_800AFB48(PartyMember* record);
void                      func_800AF8F0(PartyMember* record);
void                      func_800AFAB8(PartyMember* record);
/* One halfword per entry of the sprite upload queue. */
extern u16                D_80145A54[];
s32                       func_801DB524(u8);

/* Unless the target check fails, a target still standing makes the caster play its hit script (a party
 * caster also drops its last queued sprite upload) and the effect advances; a failed check marks the
 * battler and jumps to ABORT_STEP. A statement macro: the member declares u8 count. */
/* func_801F1474, func_801F18F4 */
#define MAGIC008_HIT_OR_ABORT(ABORT_STEP)                                                                           \
    if (!(func_801DB524(g_Battle.target_selector) & BYTE_MASK)) {                                                   \
        if (g_Battle.target_selector < BATTLE_PARTY_CHARACTERS_COUNT) {                                             \
            if (g_Game.members[g_Battle.target_selector].header.mode != 6) {                                        \
                if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {                                      \
                    Actor_SelectScript(g_Task->facing + 12);                                                        \
                    count                = --D_80145A00;                                                            \
                    (&D_80145A04)[count] = 0;                                                                       \
                    D_80145A54[count]    = 0;                                                                       \
                    (&D_80145A7C)[count] = 0;                                                                       \
                } else {                                                                                            \
                    g_Task->unk_4B = 0xFF;                                                                          \
                    func_801E257C(g_Battle.active_battler, 2);                                                      \
                }                                                                                                   \
                g_Task->unk_09 = func_800AFF98();                                                                   \
                g_Task->header.step++;                                                                              \
            }                                                                                                       \
        } else {                                                                                                    \
            if (g_BattleEnemyBattlers[g_Battle.target_selector - BATTLE_PARTY_CHARACTERS_COUNT].header.mode != 6) { \
                if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {                                      \
                    Actor_SelectScript(g_Task->facing + 12);                                                        \
                    count                = --D_80145A00;                                                            \
                    (&D_80145A04)[count] = 0;                                                                       \
                    D_80145A54[count]    = 0;                                                                       \
                    (&D_80145A7C)[count] = 0;                                                                       \
                } else {                                                                                            \
                    g_Task->unk_4B = 0xFF;                                                                          \
                    func_801E257C(g_Battle.active_battler, 2);                                                      \
                }                                                                                                   \
                g_Task->unk_09 = func_800AFF98();                                                                   \
                g_Task->header.step++;                                                                              \
            }                                                                                                       \
        }                                                                                                           \
    } else {                                                                                                        \
        g_BattleEffectBattler->param.unk_0B = 0xFF;                                                                 \
        g_Task->header.step                 = (ABORT_STEP);                                                         \
    }

/* The columns of g_BattleEffects: the retail code forms one slot base per store. */
extern BattleEffectByteColumn   D_801EC331[];
extern BattleEffectByteColumn   D_801EC332[];
extern BattleEffectByteColumn   D_801EC335[];
extern BattleEffectByteColumn   D_801EC336[];
extern BattleEffectTargetColumn D_801EC3A4[];
/* Defined later in this image; the result lands in the effect work +0x04. */
u32                             func_801F0230(void);

#endif
