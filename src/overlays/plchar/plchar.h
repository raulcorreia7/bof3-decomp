#ifndef PLCHAR_FAMILY_H
#define PLCHAR_FAMILY_H

/* Declarations shared by two or more plchar images; an image header that
 * reads one includes this file. */

#include "game.h"
#include "slus/facing.h"
#include "sys/exe.h"
#include <abs.h>

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
    if (g_SpadWork->direction_08 == g_SpadWork->unk_03) {                             \
        switch (g_SpadWork->direction_08) {                                           \
            case FIRST_FACING:                                                        \
                Actor_RequestScript(FIRST_SCRIPT);                                    \
                break;                                                                \
            case SECOND_FACING:                                                       \
                Actor_RequestScript(SECOND_SCRIPT);                                   \
                break;                                                                \
        }                                                                             \
        g_SpadWork->state_02++;                                                       \
    } else {                                                                          \
        g_SpadWork->unk_09--;                                                         \
        if (g_SpadWork->unk_09 == 0) {                                                \
            g_SpadWork->unk_09       = 2;                                             \
            g_SpadWork->direction_08 = g_SpadWork->direction_08 + g_SpadWork->unk_0B; \
            g_SpadWork->direction_08 &= 7;                                            \
            Actor_RequestScript(g_SpadWork->direction_08);                            \
        }                                                                             \
    }

/* Starts the character's walk route: picks the direction away from the work
 * record's current route index with the resident selector (Actor_GetTurnStep),
 * stores it in the direction byte at +0x03, arms the step timer at +0x09 and
 * advances the task state at +0x02. The body of every Char_StartTurn member;
 * each passes the two facing values it turns between. Every change here must
 * verify every member image. */
#define CHAR_START_TURN(FACING_BACK, FACING_AWAY)                                                    \
    if (abs(g_SpadWork->direction_08 - FACING_BACK) > abs(g_SpadWork->direction_08 - FACING_AWAY)) { \
        g_SpadWork->unk_0B = Actor_GetTurnStep(FACING_AWAY);                                         \
        g_SpadWork->unk_03 = FACING_AWAY;                                                            \
    } else {                                                                                         \
        g_SpadWork->unk_0B = Actor_GetTurnStep(FACING_BACK);                                         \
        g_SpadWork->unk_03 = FACING_BACK;                                                            \
    }                                                                                                \
    g_SpadWork->unk_09 = 2;                                                                          \
    g_SpadWork->state_02++

#define CHAR_LAUNCH_SCRIPT_PC 10

extern u32      D_801CE400;
extern Callback D_801CF900[];
extern Callback D_801CF90C[];

/* func_801CF148 (plp478), func_801CF528 (plp578), func_801CF724 (plp278), func_801CF724 (plp27a), func_801CF744 (plp457), func_801CF940 (plp247), func_801CFD20 (plp257), func_801CFFD4 (plp678), func_801D01F0 (plp467), func_801D05D0 (plp567), func_801D07CC (plp267) */
s32 Char_ProbeFacingCell(void);

/* The retail caller passes the cue word unmasked (the delay slot holds the
 * add, not a zero-extend), so this unit sees the resident dispatcher's
 * argument as a full word. */
#endif
