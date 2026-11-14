#ifndef PLCHAR_FAMILY_H
#define PLCHAR_FAMILY_H

#include "game.h"
#include "slus/facing.h"
#include "sys/exe.h"
#include "common/util.h"

/* The two route directions a character program turns between; an image that turns between
 * other directions defines both before including this file. */
#ifndef CHARACTER_FACING_AWAY
#define CHARACTER_FACING_AWAY FACING_DOWN
#define CHARACTER_FACING_BACK FACING_RIGHT
#endif

/* The type-0 loader copies the character program to 0x801CE400 and compares
 * its first word with the archive TOC cache. All 19 programs carry 33 + the
 * name-order ordinal (0x21-0x33); code follows at +0x04. */
#define PLCHAR_PROGRAM_FIRST                                     33

/* Runs one route step's script: when the facing index has reached the direction byte, it selects the script id for the turn (0x40 at the back facing, 0x41 at the away facing) and advances the task state; otherwise it counts the step timer down, and on zero re-arms it and requests the next script. The body of every Char_RunStepScript member; each passes the two facing values at which it selects script 0x40 and 0x41. */
#define CHAR_RUN_STEP_SCRIPT(FACING_SCRIPT_40, FACING_SCRIPT_41) CHAR_RUN_STEP_CASES(FACING_SCRIPT_40, 0x40, FACING_SCRIPT_41, 0x41)

/* The same step with the two switch cases written in the given order: a member whose
 * retail switch tests the 0x41 facing first passes the 0x41 case first. */
#define CHAR_RUN_STEP_CASES(FIRST_FACING, FIRST_SCRIPT, SECOND_FACING, SECOND_SCRIPT) \
    if (g_Task->direction_08 == g_Task->unk_03) {                                     \
        switch (g_Task->direction_08) {                                               \
            case FIRST_FACING:                                                        \
                Actor_RequestScript(FIRST_SCRIPT);                                    \
                break;                                                                \
            case SECOND_FACING:                                                       \
                Actor_RequestScript(SECOND_SCRIPT);                                   \
                break;                                                                \
        }                                                                             \
        g_Task->header.step++;                                                        \
    } else {                                                                          \
        g_Task->timer--;                                                              \
        if (g_Task->timer == 0) {                                                     \
            g_Task->timer        = 2;                                                 \
            g_Task->direction_08 = g_Task->direction_08 + g_Task->param.turn_step;    \
            g_Task->direction_08 &= 7;                                                \
            Actor_RequestScript(g_Task->direction_08);                                \
        }                                                                             \
    }

/* Starts the character's walk route: picks the direction away from the work record's current route index with the resident selector (Actor_GetTurnStep), stores it in the direction byte at +0x03, arms the step timer at +0x09 and advances the task state at +0x02. The body of every Char_StartTurn member; each passes the two facing values it turns between. */
#define CHAR_START_TURN(FACING_BACK, FACING_AWAY)                                            \
    if (abs(g_Task->direction_08 - FACING_BACK) > abs(g_Task->direction_08 - FACING_AWAY)) { \
        g_Task->param.turn_step = Actor_GetTurnStep(FACING_AWAY);                            \
        g_Task->unk_03          = FACING_AWAY;                                               \
    } else {                                                                                 \
        g_Task->param.turn_step = Actor_GetTurnStep(FACING_BACK);                            \
        g_Task->unk_03          = FACING_BACK;                                               \
    }                                                                                        \
    g_Task->timer = 2;                                                                       \
    g_Task->header.step++

/* Runs this image's turn preparation, requests the script of the character's current facing and sets the task to state 0xB, step 1. The body of every character's facing-turn start; each passes its preparation function. */
#define CHAR_START_FACING_TURN(PREPARE)                         \
    PREPARE();                                                  \
    Actor_RequestScript((g_Task->direction_08 - 1) / 2 + 0x42); \
    g_Task->unk_0A = 0xB;                                       \
    g_Task->unk_03 = 1

/* Chooses a direction and requests its script: steps direction_08 to a free neighbouring facing when it is even (CHECK reports whether the facing is free), then runs this image's turn preparation PREPARE and starts the facing script. The body of every Char_FaceFreeDirection; each passes its two functions. */
/* Char_FaceFreeDirection (plp016 0x801CF7B4, plp026 0x801CFBD8, plp056 0x801CF9DC, plp267 0x801CEEB0, plp467
 * 0x801CE8D4, plp567 0x801CECB4, plp678 0x801CE6B8) */
#define CHAR_FACE_FREE_DIRECTION(CHECK, PREPARE)                                \
    u8 direction;                                                               \
                                                                                \
    direction = g_Task->direction_08;                                           \
    if (!(direction & 1)) {                                                     \
        g_Task->direction_08 = (direction - 1) & 7;                             \
        if (!(CHECK() & 0xFF)) {                                                \
            g_Task->direction_08 = (g_Task->direction_08 + 2) & 7;              \
            if (!(CHECK() & 0xFF)) {                                            \
                g_Task->direction_08 = (g_Task->direction_08 - 2) & 7;          \
            }                                                                   \
        }                                                                       \
    }                                                                           \
    PREPARE();                                                                  \
    Actor_RequestScript((((s32)(g_Task->direction_08 - 1) / 2) + 0x42) & 0xFF); \
    g_Task->param.unk_0B = 0;                                                   \
    g_Task->unk_0A       = 0xB;                                                 \
    g_Task->unk_03       = 1

/* Probes facing clearance for the character's free-direction choice; sets g_Task->unk_2B to 0 when blocked. */
#define CHAR_PROBE_FACING_CLEARANCE(dist, x, y)                                                        \
    {                                                                                                  \
        g_Task->unk_2B = 1;                                                                            \
        x              = g_Task->pos.x.fixed + g_FacingSteps[FACING_RIGHT].x;                          \
        y              = g_Task->pos.y.fixed + g_FacingSteps[FACING_RIGHT].y;                          \
        dist           = Area_ReadStepHeight(x, y, FACING_RIGHT);                                      \
        if (SP_REF(u8, 0x0u) != 0 && dist >= 65 && COORD_INT(g_Task->pos.z) < Area_ReadHeight(x, y)) { \
            g_Task->unk_2B = 0;                                                                        \
        }                                                                                              \
        x    = g_Task->pos.x.fixed + g_FacingSteps[FACING_DOWN].x;                                     \
        y    = g_Task->pos.y.fixed + g_FacingSteps[FACING_DOWN].y;                                     \
        dist = Area_ReadStepHeight(x, y, FACING_DOWN);                                                 \
        if (SP_REF(u8, 0x0u) != 0 && dist >= 65 && COORD_INT(g_Task->pos.z) < Area_ReadHeight(x, y)) { \
            g_Task->unk_2B = 0;                                                                        \
        }                                                                                              \
    }

void Char_SpawnActor(s32 spawn_kind, s32 spawn_x, s32 spawn_y);
void Char_SpawnLinkedActor(s32 spawn_kind, s32 spawn_x, s32 spawn_y, s32 code);
void Area_ClearCell(s32 x, s32 y);

#define CHAR_PROBE_CELL_CODE(CALLEE)                                       \
    s32 cell;                                                              \
    s32 i;                                                                 \
    u32 roll;                                                              \
    u8* record;                                                            \
                                                                           \
    cell = Area_GetCellCode(x, y);                                         \
    if ((u8)(cell + 0x10) < 2 || (cell & BYTE_MASK) == 0xF4) {             \
        CALLEE(0, x, y, cell & BYTE_MASK);                                 \
        if ((RANDOM_MASK(7)) >= 6) {                                       \
            CALLEE(4, x, y, cell & BYTE_MASK);                             \
        }                                                                  \
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 11));                      \
        return 1;                                                          \
    }                                                                      \
    if ((u8)(cell + 0xA) < 2) {                                            \
        CALLEE(0, x, y, cell & BYTE_MASK);                                 \
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 11));                      \
        roll = RANDOM_MASK(0xF);                                           \
        if (roll < 7) {                                                    \
            CALLEE(3, x, y, cell & BYTE_MASK);                             \
            record = Item_GetRecord(ITEM_CAT_ITEM, ITEM_BERRIES);          \
            for (i = 0; i < 12; i++) {                                     \
                g_TextVariables[0][i] = record[i];                         \
            }                                                              \
            D_801490E4[0] = 0;                                             \
            if (Item_Add(ITEM_CAT_ITEM, ITEM_BERRIES, 1, 0) & BYTE_MASK) { \
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));               \
                Message_Request(2);                                        \
            } else {                                                       \
                Message_Request(3);                                        \
            }                                                              \
            g_Task->param.unk_0B = 2;                                      \
        } else if (roll >= 12) {                                           \
            CALLEE(2, x, y, cell & BYTE_MASK);                             \
            func_801C308C(0);                                              \
            Char_LoseHP(1, g_Game.current->chr.character_id);              \
            Message_Request(0xD9);                                         \
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;                   \
            g_Task->param.unk_0B = 1;                                      \
        }                                                                  \
        g_GameStateIndex = GAME_REQUEST_MESSAGE;                           \
        return 1;                                                          \
    }                                                                      \
    return 0;

#define CHAR_LAUNCH_SCRIPT_PC 10

extern u32      D_801CE400;
extern Callback D_801CF900[];
extern Callback D_801CF90C[];

/* func_801CF148 (plp478), func_801CF528 (plp578), func_801CF724 (plp278), func_801CF724 (plp27a), func_801CF744
   (plp457), func_801CF940 (plp247), func_801CFD20 (plp257), func_801CFFD4 (plp678), func_801D01F0 (plp467),
   func_801D05D0 (plp567), func_801D07CC (plp267) */
s32 func_801B2D00(s32 selector);
s32 Char_ProbeFacingCell(void);

/* Probes the cell one facing step (doubled) from the indexed route record for a party member. */
#define PLCHAR_PROBE_FACING_FOLLOWER(index)                                                                             \
    {                                                                                                                   \
        s32 i;                                                                                                          \
        s32 x = g_SpawnedActors[index].pos.x.fixed + g_FacingSteps[g_Task->direction_08].x * 2;                            \
        s32 y = g_SpawnedActors[index].pos.y.fixed + g_FacingSteps[g_Task->direction_08].y * 2;                            \
        for (i = 1; i < g_PartySize; i++) {                                                                             \
            if (func_801BDD58(x, y, COORD_INT(g_SpawnedActors[index].pos.z), 1, (Actor*)&g_Game.members[i]) & BYTE_MASK) { \
                return 1;                                                                                               \
            }                                                                                                           \
        }                                                                                                               \
        return 0;                                                                                                       \
    }

/* The retail caller passes the cue word unmasked (the delay slot holds the
 * add, not a zero-extend), so this unit sees the resident dispatcher's
 * argument as a full word. */
#endif
