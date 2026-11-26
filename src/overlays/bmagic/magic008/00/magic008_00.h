#ifndef OVERLAY_BMAGIC_MAGIC008_00_H
#define OVERLAY_BMAGIC_MAGIC008_00_H

/* The bmagic/magic008/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* header.mode of the strike effect: g_BMagicEffectModes runs BMagic_SkillStrikeEffectUpdate. */
#define BMAGIC_SKILL_STRIKE_EFFECT_STRIKE       2

/* The follow-up effect id of the task: the strike of Mind Flay launches one at the target, the others none. */
#define BMAGIC_SKILL_STRIKE_FOLLOW_UP_NONE      0xFF
#define BMAGIC_SKILL_STRIKE_FOLLOW_UP_MIND_FLAY 7

#define MAGIC008_EARLY_STEP_COUNT               7
#define MAGIC008_STEP_COUNT                     10

typedef struct Magic008EarlySteps {
    Callback steps[MAGIC008_EARLY_STEP_COUNT];
} Magic008EarlySteps;

typedef struct Magic008Steps {
    Callback steps[MAGIC008_STEP_COUNT];
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

extern u8                 D_800B6BF0[];
extern Magic008FirstSteps D_801EEC04;

extern Magic008SecondSteps D_801EEC14;
extern Magic008FirstSteps  D_801EEC20;
extern Magic008FirstSteps  D_801EEC30;
extern Magic008SecondSteps D_801EEC40;
/* D_801EEC4C */
extern Magic008SecondSteps g_BMagicSkillStrikeModes;
extern BMagicEffectSteps   D_801EEC58;
extern Magic008ThirdSteps  D_801EEC70;
/* D_801EEC84 */
extern Magic008FirstSteps  g_BMagicSkillStrikeSteps;

extern BMagicEffectSteps  D_801EEC94;
extern Magic008EarlySteps D_801EECAC;
extern Magic008Steps      D_801EECC8;
extern Offset2            D_801F1C04[];
/* func_800AED5C */
u8                        Battle_CanTarget(s32 selector, u32 battler_index);
/* The battle/battle/15 sprite-cell routines, called with a battler or the effect work record. */
/* func_800AFB48 */
u32                       Battle_CopyCellPalette(PartyMember* record);
/* func_800AFAB8 */
void                      Battle_ClearCellPaletteEntry(PartyMember* record);
/* One halfword per entry of the sprite upload queue. */
extern u16                D_80145A54[];

/* Unless the target check fails, a target still standing makes the caster play its hit script (a party
 * caster also drops its last queued sprite upload) and the effect advances; a failed check marks the
 * battler and jumps to ABORT_STEP. A statement macro: the member declares u8 count. */
/* func_801F1474, func_801F18F4 */
#define MAGIC008_HIT_OR_ABORT(ABORT_STEP)                                                                           \
    if (!(Battle_SlotIsBlocked(g_Battle.target_selector) & BYTE_MASK)) {                                            \
        if (g_Battle.target_selector < BATTLE_PARTY_CHARACTERS_COUNT) {                                             \
            if (g_Game.members[g_Battle.target_selector].header.mode != 6) {                                        \
                if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {                                      \
                    Script_Select(SELF(PartyMember)->facing + 12);                                                  \
                    count                = --g_GfxTransferCount;                                                    \
                    (&D_80145A04)[count] = 0;                                                                       \
                    D_80145A54[count]    = 0;                                                                       \
                    (&D_80145A7C)[count] = 0;                                                                       \
                } else {                                                                                            \
                    SELF(PartyMember)->unk_4B = 0xFF;                                                               \
                    func_801E257C(g_Battle.active_battler, 2);                                                      \
                }                                                                                                   \
                SELF(PartyMember)->unk_09 = func_800AFF98();                                                        \
                SELF(PartyMember)->header.step++;                                                                   \
            }                                                                                                       \
        } else {                                                                                                    \
            if (g_BattleEnemyBattlers[g_Battle.target_selector - BATTLE_PARTY_CHARACTERS_COUNT].header.mode != 6) { \
                if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {                                      \
                    Script_Select(SELF(PartyMember)->facing + 12);                                                  \
                    count                = --g_GfxTransferCount;                                                    \
                    (&D_80145A04)[count] = 0;                                                                       \
                    D_80145A54[count]    = 0;                                                                       \
                    (&D_80145A7C)[count] = 0;                                                                       \
                } else {                                                                                            \
                    SELF(PartyMember)->unk_4B = 0xFF;                                                               \
                    func_801E257C(g_Battle.active_battler, 2);                                                      \
                }                                                                                                   \
                SELF(PartyMember)->unk_09 = func_800AFF98();                                                        \
                SELF(PartyMember)->header.step++;                                                                   \
            }                                                                                                       \
        }                                                                                                           \
    } else {                                                                                                        \
        g_BattleEffectBattler->param.unk_0B = 0xFF;                                                                 \
        SELF(PartyMember)->header.step      = (ABORT_STEP);                                                         \
    }

/* The columns of g_BattleEffects: the retail code forms one slot base per store. */
extern BattleEffectByteColumn   D_801EC331[];
extern BattleEffectByteColumn   D_801EC332[];
extern BattleEffectByteColumn   D_801EC335[];
extern BattleEffectByteColumn   D_801EC336[];
extern BattleEffectTargetColumn D_801EC3A4[];
/* Defined later in this image; the result lands in the effect work +0x04. */
/* func_801F0230 */
u32                             BMagic_SkillStrikeFollowUp(void);

/* Advance the effect animation, count the timer down and at zero play the given hit SE, mark the target
 * damaged and step. A statement macro: the member declares u8 timer. */
#define MAGIC008_COUNT_DOWN_MARK_DAMAGED(se_id)                \
    Script_AnimStepOnce();                                     \
    timer                     = SELF(PartyMember)->unk_09 - 1; \
    SELF(PartyMember)->unk_09 = timer;                         \
    if (!(timer & BYTE_MASK)) {                                \
        Battle_PlayActiveBattlerSE((se_id), 0);                \
        Battle_MarkDamaged(g_Battle.target_selector);          \
        SELF(PartyMember)->header.step += 1;                   \
    }

/* Release the active battler and advance the effect mode once the effect target's byte 0x0B is 0xFF. */
#define MAGIC008_RELEASE_ACTIVE_AT_END()                                     \
    if (SELF(PartyMember)->param.unk_0B == 0xFF) {                           \
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY; \
        Battle_SelectActiveBattlerScript(4, 0);                              \
        SELF(PartyMember)->header.mode += 1;                                 \
    }

#endif
