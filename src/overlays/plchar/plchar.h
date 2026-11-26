#ifndef PLCHAR_FAMILY_H
#define PLCHAR_FAMILY_H

#include "game.h"
#include "common/facing.h"
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

/* Runs one route step's script: when the facing index has reached the direction byte, it selects the script id for the turn (0x40 at the back facing, 0x41 at the away facing) and advances the task state; otherwise it counts the step timer down, and on zero re-arms it and requests the next script. The body of every PlChar_RunStepScript member; each passes the two facing values at which it selects script 0x40 and 0x41. */
#define CHAR_RUN_STEP_SCRIPT(FACING_SCRIPT_40, FACING_SCRIPT_41) CHAR_RUN_STEP_CASES(FACING_SCRIPT_40, 0x40, FACING_SCRIPT_41, 0x41)

/* The same step with the two switch cases written in the given order: a member whose
 * retail switch tests the 0x41 facing first passes the 0x41 case first. */
#define CHAR_RUN_STEP_CASES(FIRST_FACING, FIRST_SCRIPT, SECOND_FACING, SECOND_SCRIPT)        \
    if (SELF(Actor)->direction == SELF(Actor)->unk_03) {                                     \
        switch (SELF(Actor)->direction) {                                                    \
            case FIRST_FACING:                                                               \
                Script_Request(FIRST_SCRIPT);                                                \
                break;                                                                       \
            case SECOND_FACING:                                                              \
                Script_Request(SECOND_SCRIPT);                                               \
                break;                                                                       \
        }                                                                                    \
        SELF(Actor)->header.step++;                                                          \
    } else {                                                                                 \
        SELF(Actor)->timer--;                                                                \
        if (SELF(Actor)->timer == 0) {                                                       \
            SELF(Actor)->timer     = 2;                                                      \
            SELF(Actor)->direction = SELF(Actor)->direction + SELF(Actor)->param.turn_delta; \
            SELF(Actor)->direction &= 7;                                                     \
            Script_Request(SELF(Actor)->direction);                                          \
        }                                                                                    \
    }

/* Starts the character's walk route: picks the direction away from the work record's current route index with the resident selector (Actor_GetTurnStep), stores it in the direction byte at +0x03, arms the step timer at +0x09 and advances the task state at +0x02. The body of every PlChar_StartTurn member; each passes the two facing values it turns between. */
#define CHAR_START_TURN(FACING_BACK, FACING_AWAY)                                                \
    if (abs(SELF(Actor)->direction - FACING_BACK) > abs(SELF(Actor)->direction - FACING_AWAY)) { \
        SELF(Actor)->param.turn_delta = Actor_GetTurnStep(FACING_AWAY);                          \
        SELF(Actor)->unk_03           = FACING_AWAY;                                             \
    } else {                                                                                     \
        SELF(Actor)->param.turn_delta = Actor_GetTurnStep(FACING_BACK);                          \
        SELF(Actor)->unk_03           = FACING_BACK;                                             \
    }                                                                                            \
    SELF(Actor)->timer = 2;                                                                      \
    SELF(Actor)->header.step++

/* Runs this image's turn preparation, requests the script of the character's current facing and sets the task to state 0xB, step 1. The body of every character's facing-turn start; each passes its preparation function. */
#define CHAR_START_FACING_TURN(PREPARE)                      \
    PREPARE();                                               \
    Script_Request((SELF(Actor)->direction - 1) / 2 + 0x42); \
    SELF(Actor)->unk_0A = 0xB;                               \
    SELF(Actor)->unk_03 = 1

/* Chooses a direction and requests its script: steps direction to a free neighbouring facing when it is even (CHECK reports whether the facing is free), then runs this image's turn preparation PREPARE and starts the facing script. The body of every PlChar_FaceFreeDirection; each passes its two functions. */
/* PlChar_FaceFreeDirection (plp016 0x801CF7B4, plp026 0x801CFBD8, plp056 0x801CF9DC, plp267 0x801CEEB0, plp467
 * 0x801CE8D4, plp567 0x801CECB4, plp678 0x801CE6B8) */
#define CHAR_FACE_FREE_DIRECTION(CHECK, PREPARE)                             \
    u8 direction;                                                            \
                                                                             \
    direction = SELF(Actor)->direction;                                      \
    if (!(direction & 1)) {                                                  \
        SELF(Actor)->direction = (direction - 1) & 7;                        \
        if (!(CHECK() & 0xFF)) {                                             \
            SELF(Actor)->direction = (SELF(Actor)->direction + 2) & 7;       \
            if (!(CHECK() & 0xFF)) {                                         \
                SELF(Actor)->direction = (SELF(Actor)->direction - 2) & 7;   \
            }                                                                \
        }                                                                    \
    }                                                                        \
    PREPARE();                                                               \
    Script_Request((((s32)(SELF(Actor)->direction - 1) / 2) + 0x42) & 0xFF); \
    SELF(Actor)->param.unk_0B = 0;                                           \
    SELF(Actor)->unk_0A       = 0xB;                                         \
    SELF(Actor)->unk_03       = 1

/* Probes facing clearance for the character's free-direction choice; sets SELF(Actor)->unk_2B to 0 when blocked. */
#define CHAR_PROBE_FACING_CLEARANCE(dist, x, y)                                                             \
    {                                                                                                       \
        SELF(Actor)->unk_2B = 1;                                                                            \
        x                   = SELF(Actor)->pos.x.fixed + g_FacingSteps[FACING_RIGHT].x;                     \
        y                   = SELF(Actor)->pos.y.fixed + g_FacingSteps[FACING_RIGHT].y;                     \
        dist                = Area_HeightReadStep(x, y, FACING_RIGHT);                                      \
        if (SP_REF(u8, 0x0u) != 0 && dist >= 65 && COORD_INT(SELF(Actor)->pos.z) < Area_HeightRead(x, y)) { \
            SELF(Actor)->unk_2B = 0;                                                                        \
        }                                                                                                   \
        x    = SELF(Actor)->pos.x.fixed + g_FacingSteps[FACING_DOWN].x;                                     \
        y    = SELF(Actor)->pos.y.fixed + g_FacingSteps[FACING_DOWN].y;                                     \
        dist = Area_HeightReadStep(x, y, FACING_DOWN);                                                      \
        if (SP_REF(u8, 0x0u) != 0 && dist >= 65 && COORD_INT(SELF(Actor)->pos.z) < Area_HeightRead(x, y)) { \
            SELF(Actor)->unk_2B = 0;                                                                        \
        }                                                                                                   \
    }

/* Turns an even facing one step back, probes the clearance ahead and requests the script of the facing the character
 * now holds, then advances the step. The body of every plchar program's free-facing start. */
/* func_801CF750 (plp015), func_801CEE4C (plp257), func_801CE870 (plp457), func_801CF37C (plp056), func_801CE654 (plp567 and plp578), func_801CFB74 (plp025) */
#define CHAR_START_FREE_FACING                            \
    s16 dist;                                             \
    s32 x;                                                \
    s32 y;                                                \
    u8  direction;                                        \
                                                          \
    direction = SELF(Actor)->direction;                   \
    if (!(direction & 1)) {                               \
        SELF(Actor)->direction = (direction - 1) & 7;     \
    }                                                     \
    CHAR_PROBE_FACING_CLEARANCE(dist, x, y)               \
    Script_Request((SELF(Actor)->direction >> 1) + 0x42); \
    SELF(Actor)->header.step++

void PlChar_SpawnActor(s32 spawn_type, s32 vx, s32 spawn_y);
void PlChar_SpawnLinkedActor(s32 spawn_type, s32 vx, s32 spawn_y, s32 code);

#define CHAR_CELL_CODE_BLOCKS_CHARACTER(cell) ((u8)((cell) + 0x10) < 2 || ((cell) & BYTE_MASK) == 0xF4 || (u8)((cell) + 0xA) < 2)

#define CHAR_PROBE_CELL_CODE(CALLEE)                                            \
    s32 cell;                                                                   \
    s32 i;                                                                      \
    u32 roll;                                                                   \
    u8* record;                                                                 \
                                                                                \
    cell = Area_CellGetCode(x, y);                                              \
    if ((u8)(cell + 0x10) < 2 || (cell & BYTE_MASK) == 0xF4) {                  \
        CALLEE(0, x, y, cell & BYTE_MASK);                                      \
        if ((RANDOM_MASK(7)) >= 6) {                                            \
            CALLEE(4, x, y, cell & BYTE_MASK);                                  \
        }                                                                       \
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 11));                             \
        return 1;                                                               \
    }                                                                           \
    if ((u8)(cell + 0xA) < 2) {                                                 \
        CALLEE(0, x, y, cell & BYTE_MASK);                                      \
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 11));                             \
        roll = RANDOM_MASK(0xF);                                                \
        if (roll < 7) {                                                         \
            CALLEE(3, x, y, cell & BYTE_MASK);                                  \
            record = Item_GetRecord(ITEM_CATEGORY_ITEM, ITEM_BERRIES);          \
            for (i = 0; i < 12; i++) {                                          \
                g_TextVariables[0][i] = record[i];                              \
            }                                                                   \
            D_801490E4[0] = 0;                                                  \
            if (Item_Add(ITEM_CATEGORY_ITEM, ITEM_BERRIES, 1, 0) & BYTE_MASK) { \
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));                      \
                UI_MessageRequest(MSG_SYSTEM_FOUND_ITEM);                       \
            } else {                                                            \
                UI_MessageRequest(MSG_SYSTEM_FOUND_ITEM_NO_ROOM);               \
            }                                                                   \
            SELF(Actor)->param.unk_0B = 2;                                      \
        } else if (roll >= 12) {                                                \
            CALLEE(2, x, y, cell & BYTE_MASK);                                  \
            Party_FlashDamage(PARTY_DAMAGE_COLOR_RED);                          \
            Char_HPLose(1, g_Game.current->chr.character_id);                   \
            UI_MessageRequest(MSG_SYSTEM_STUNG_BY_CATERPILLAR);                 \
            g_GameStateIndex          = GAME_REQUEST_MESSAGE;                   \
            SELF(Actor)->param.unk_0B = 1;                                      \
        }                                                                       \
        g_GameStateIndex = GAME_REQUEST_MESSAGE;                                \
        return 1;                                                               \
    }                                                                           \
    return 0;

#define CHAR_LAUNCH_SCRIPT_PC 10

extern u32      D_801CE400;
extern Callback D_801CF900[];
extern Callback D_801CF90C[];

/* func_801CF148 (plp478), func_801CF528 (plp578), func_801CF724 (plp278), func_801CF724 (plp27a), func_801CF744
   (plp457), func_801CF940 (plp247), func_801CFD20 (plp257), func_801CFFD4 (plp678), func_801D01F0 (plp467),
   func_801D05D0 (plp567), func_801D07CC (plp267) */
s32 func_801B2D00(s32 selector);
s32 PlChar_ProbeFacingCell(void);
s32 PlChar_ProbeCellSpawn(s16 x, s16 y);
s32 PlChar_ProbeCellSpawn(s16 x, s16 y);

/* Probes the cell one facing step (doubled) from the indexed route record for a party member. */
#define PLCHAR_PROBE_FACING_FOLLOWER(index)                                                                                  \
    {                                                                                                                        \
        s32 i;                                                                                                               \
        s32 x = g_SpawnedActors[index].pos.x.fixed + g_FacingSteps[SELF(Actor)->direction].x * 2;                            \
        s32 y = g_SpawnedActors[index].pos.y.fixed + g_FacingSteps[SELF(Actor)->direction].y * 2;                            \
        for (i = 1; i < g_PartySize; i++) {                                                                                  \
            if (Actor_IsInRange(x, y, COORD_INT(g_SpawnedActors[index].pos.z), 1, (Actor*)&g_Game.members[i]) & BYTE_MASK) { \
                return 1;                                                                                                    \
            }                                                                                                                \
        }                                                                                                                    \
        return 0;                                                                                                            \
    }

/* The retail caller passes the cue word unmasked (the delay slot holds the
 * add, not a zero-extend), so this unit sees the resident dispatcher's
 * argument as a full word. */
#endif
