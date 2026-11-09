#ifndef MENU_CLOCK_H
#define MENU_CLOCK_H

#include "types.h"

/* The play clock and the two countdown timers: hours, minutes, seconds and thirtieths of a second, one byte each.
 * The play clock stops at 99:59:59; the timers count down through the same fields. */

#define GAME_CLOCK_THIRTIETHS_PER_SECOND         30
#define GAME_CLOCK_SECONDS_PER_MINUTE            60
#define GAME_CLOCK_MINUTES_PER_HOUR              60
#define GAME_CLOCK_MAX_HOURS                     99

/* Hours, minutes and seconds as the low three bytes of the clock read as one word. */
#define GAME_CLOCK_PACK(hours, minutes, seconds) ((u32)(hours) | ((minutes) << 8) | ((seconds) << 16))

/* The play clock stops here. */
#define GAME_CLOCK_STOPPED                       GAME_CLOCK_PACK(GAME_CLOCK_MAX_HOURS, 59, 59)

#define GAME_CLOCK_SIZE                          0x04

typedef struct GameClock {
    u8 hours;
    u8 minutes;
    u8 seconds;
    u8 thirtieths;
} GameClock;

ASSERT_SIZE(GameClock, GAME_CLOCK_SIZE);
ASSERT_OFFSET(GameClock, hours, 0x00);
ASSERT_OFFSET(GameClock, thirtieths, 0x03);

/* D_80144FC0 */
extern GameClock g_PlayClock;
/* The countdown timers of the celerity and bonebreak abilities. Both lie in the saved block, at save offsets
 * SAVE_CELERITY_TIMER and SAVE_BONEBREAK_TIMER. */
/* D_80145554 */
extern GameClock g_GameCelerityTimer;
/* D_80145558 */
extern GameClock g_GameBonebreakTimer;

#endif
