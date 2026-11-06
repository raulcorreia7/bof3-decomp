#ifndef MENU_CLOCK_H
#define MENU_CLOCK_H

#include "types.h"

/*
 * Play clock and countdown timers, four bytes each: hours, minutes, seconds,
 * and thirtieths of a second.
 *
 * Observed in etc/game/00's tick loop: the thirtieths byte rolls at 0x1E, seconds
 * and minutes at 0x3C, and the clock stops at the 0x3B3B63 sentinel
 * (99:59:59) rather than incrementing past it. The two countdown timers use
 * the same fields in reverse, borrowing at the same boundaries.
 *
 * The same bytes are formatted for display by the shop, commu00, and etc/game/01
 * overlays, so the layout is shared rather than target-local.
 */

#define GAME_CLOCK_THIRTIETHS_PER_SECOND 0x1E
#define GAME_CLOCK_SECONDS_PER_MINUTE    0x3C
#define GAME_CLOCK_MINUTES_PER_HOUR      0x3C
#define GAME_CLOCK_MAX_HOURS             0x63

/* Hours:minutes:seconds of a stopped clock, low three bytes. */
#define GAME_CLOCK_STOPPED               0x3B3B63u

#define GAME_CLOCK_SIZE                  0x04

typedef struct GameClock {
    u8 hours_00;
    u8 minutes_01;
    u8 seconds_02;
    u8 thirtieths_03;
} GameClock;

ASSERT_SIZE(GameClock, GAME_CLOCK_SIZE);
ASSERT_OFFSET(GameClock, hours_00, 0x00);
ASSERT_OFFSET(GameClock, thirtieths_03, 0x03);

/* D_80144FC0 */
extern GameClock g_PlayClock;
/* The countdown timers of the celerity and bonebreak abilities. Both lie in the saved block, at save offsets
 * SAVE_CELERITY_TIMER and SAVE_BONEBREAK_TIMER. */
/* D_80145554 */
extern GameClock g_GameCelerityTimer;
/* D_80145558 */
extern GameClock g_GameBonebreakTimer;

#endif
