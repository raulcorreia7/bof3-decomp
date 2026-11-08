#ifndef PLCHAR_FAMILY_H
#define PLCHAR_FAMILY_H

/* Declarations shared by two or more plchar images; an image header that
 * reads one includes this file. */

#include "game.h"
#include "slus/facing.h"
#include "sys/exe.h"
#include "common/util.h"

/* The two route directions a character program turns between; an image that turns between
 * other directions defines both before including this file. */
#ifndef CHARACTER_FACING_AWAY
#define CHARACTER_FACING_AWAY 5
#define CHARACTER_FACING_BACK 3
#endif

/* The type-0 loader copies the character program to 0x801CE400 and compares
 * its first word with the archive TOC cache. All 19 programs carry 33 + the
 * name-order ordinal (0x21-0x33); code follows at +0x04. */
#define PLCHAR_PROGRAM_FIRST 33

/* Runs one route step's script: when the facing index has reached the
 * direction byte, it selects the script id for the turn (0x40 at the back
 * facing, 0x41 at the away facing) and advances the task state; otherwise it
 * counts the step timer down, and on zero re-arms it and requests the next
 * script. The body of every Char_RunStepScript member; each passes the two
 * facing values at which it selects script 0x40 and 0x41. Every change here must verify every member
 * image. */
#define CHAR_RUN_STEP_SCRIPT(FACING_SCRIPT_40, FACING_SCRIPT_41)        \
    CHAR_RUN_STEP_CASES(FACING_SCRIPT_40, 0x40, FACING_SCRIPT_41, 0x41)

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

/* Starts the character's walk route: picks the direction away from the work
 * record's current route index with the resident selector (Actor_GetTurnStep),
 * stores it in the direction byte at +0x03, arms the step timer at +0x09 and
 * advances the task state at +0x02. The body of every Char_StartTurn member;
 * each passes the two facing values it turns between. Every change here must
 * verify every member image. */
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

/* The cell probe of the plchar programs that react to map cells 0xF2 and 0xF8 with the
 * shared Char_SpawnActor: 0xF2 spawns a field record (and sometimes a second) and
 * 0xF8 hands out the item 0x56. Every change here must verify every member image. */
#define CHAR_PROBE_CELL_SPAWN()                                            \
    s32 cell;                                                              \
    s32 i;                                                                 \
    u32 roll;                                                              \
    s32 spawn_cue;                                                         \
    u8* record;                                                            \
                                                                           \
    cell = Area_GetCellCode(x, y) & BYTE_MASK;                             \
    if (cell == 0xF2) {                                                    \
        if ((Actor_FindFreeSlot() & BYTE_MASK) != GAME_NONE) {             \
            Char_SpawnActor(0, x, y);                                      \
            roll = RANDOM_MASK(0xF);                                       \
            if (roll >= 13) {                                              \
                spawn_cue = 5;                                             \
                if (roll < 15) {                                           \
                    spawn_cue = 2;                                         \
                }                                                          \
                if ((g_GameRequestFlags & 6) && !(RANDOM_MASK(3))) {       \
                    spawn_cue = (spawn_cue & BYTE_MASK) * 20;              \
                }                                                          \
                func_801B5E58(spawn_cue & BYTE_MASK);                      \
                Char_SpawnActor(1, x, y);                                  \
            }                                                              \
            g_Task->param.unk_0B = 1;                                      \
        }                                                                  \
        Area_ClearCell(x, y);                                              \
        return 1;                                                          \
    }                                                                      \
    if (cell == 0xF8) {                                                    \
        Char_SpawnActor(0, x, y);                                          \
        record = Item_GetRecord(ITEM_CAT_ITEM, ITEM_HORSERADISH);          \
        for (i = 0; i < 12; i++) {                                         \
            g_TextVariables[0][i] = record[i];                             \
        }                                                                  \
        D_801490E4[0] = 0;                                                 \
        if (Item_Add(ITEM_CAT_ITEM, ITEM_HORSERADISH, 1, 0) & BYTE_MASK) { \
            SND_PlayCue(EMI_CUE_ID(1, 6));                                 \
            Resource_RequestArea(2);                                       \
        } else {                                                           \
            Resource_RequestArea(3);                                       \
        }                                                                  \
        g_GameStateIndex     = 2;                                          \
        g_Task->param.unk_0B = 1;                                          \
        Area_ClearCell(x, y);                                              \
        return 1;                                                          \
    }                                                                      \
    return 0

void Char_SpawnActor(s32 arg0, s32 arg1, s32 arg2);
void Area_ClearCell(s32 x, s32 y);

/* The cell-code probe shared by the plchar character programs: the three cell codes
 * that react start the image's own effect spawner CALLEE. Every change here must
 * verify every member image. */
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
        SND_PlayCue(EMI_CUE_ID(1, 11));                                    \
        return 1;                                                          \
    }                                                                      \
    if ((u8)(cell + 0xA) < 2) {                                            \
        CALLEE(0, x, y, cell & BYTE_MASK);                                 \
        SND_PlayCue(EMI_CUE_ID(1, 11));                                    \
        roll = RANDOM_MASK(0xF);                                           \
        if (roll < 7) {                                                    \
            CALLEE(3, x, y, cell & BYTE_MASK);                             \
            record = Item_GetRecord(ITEM_CAT_ITEM, ITEM_BERRIES);          \
            for (i = 0; i < 12; i++) {                                     \
                g_TextVariables[0][i] = record[i];                         \
            }                                                              \
            D_801490E4[0] = 0;                                             \
            if (Item_Add(ITEM_CAT_ITEM, ITEM_BERRIES, 1, 0) & BYTE_MASK) { \
                SND_PlayCue(EMI_CUE_ID(1, 6));                             \
                Resource_RequestArea(2);                                   \
            } else {                                                       \
                Resource_RequestArea(3);                                   \
            }                                                              \
            g_Task->param.unk_0B = 2;                                      \
        } else if (roll >= 12) {                                           \
            CALLEE(2, x, y, cell & BYTE_MASK);                             \
            func_801C308C(0);                                              \
            Char_LoseHP(1, g_Game.current->chr.character_id);              \
            Resource_RequestArea(0xD9);                                    \
            g_GameStateIndex     = 2;                                      \
            g_Task->param.unk_0B = 1;                                      \
        }                                                                  \
        g_GameStateIndex = 2;                                              \
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

/* The retail caller passes the cue word unmasked (the delay slot holds the
 * add, not a zero-extend), so this unit sees the resident dispatcher's
 * argument as a full word. */
#endif
