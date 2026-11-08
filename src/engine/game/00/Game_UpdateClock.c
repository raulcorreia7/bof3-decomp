#include "game_00.h"

/* func_80198CAC */
MATCH void Game_UpdateClock(void) {
    GameClock* clock;
    GameClock* timer1;
    GameClock* timer2;
    u8         next;
    u8         hours;

    if (g_GameStateIndex != GAME_REQUEST_SCENE_CAMERA) {
        clock = &g_PlayClock;
        if ((*(volatile u32*)clock & 0xFFFFFFu) != GAME_CLOCK_STOPPED) {
            if (++clock->thirtieths >= GAME_CLOCK_THIRTIETHS_PER_SECOND) {
                clock->thirtieths = 0;
                if (++clock->seconds >= GAME_CLOCK_SECONDS_PER_MINUTE) {
                    clock->seconds = 0;
                    if (++clock->minutes >= GAME_CLOCK_MINUTES_PER_HOUR) {
                        hours = clock->hours;
                        if (hours < GAME_CLOCK_MAX_HOURS) {
                            clock->minutes = 0;
                            clock->hours   = hours + 1;
                        } else {
                            clock->minutes = GAME_CLOCK_MINUTES_PER_HOUR - 1;
                            clock->seconds = GAME_CLOCK_SECONDS_PER_MINUTE - 1;
                        }
                    }
                }
            }
        }
        timer1 = &g_GameCelerityTimer;
        if (*(volatile u32*)timer1 != 0u) {
            next               = timer1->thirtieths - 1;
            timer1->thirtieths = next;
            if ((s8)next < 0) {
                timer1->thirtieths = GAME_CLOCK_THIRTIETHS_PER_SECOND - 1;
                next               = timer1->seconds - 1;
                timer1->seconds    = next;
                if ((s8)next < 0) {
                    timer1->seconds = GAME_CLOCK_SECONDS_PER_MINUTE - 1;
                    next            = timer1->minutes - 1;
                    timer1->minutes = next;
                    if ((s8)next < 0) {
                        next = timer1->hours;
                        if (next != 0u) {
                            timer1->minutes = GAME_CLOCK_MINUTES_PER_HOUR - 1;
                            timer1->hours   = next - 1;
                        } else {
                            timer1->minutes = 0;
                            timer1->seconds = 0;
                        }
                    }
                }
            }
        }
        timer2 = &g_GameBonebreakTimer;
        if (*(volatile u32*)timer2 != 0u) {
            next               = timer2->thirtieths - 1;
            timer2->thirtieths = next;
            if ((s8)next < 0) {
                timer2->thirtieths = GAME_CLOCK_THIRTIETHS_PER_SECOND - 1;
                next               = timer2->seconds - 1;
                timer2->seconds    = next;
                if ((s8)next < 0) {
                    timer2->seconds = GAME_CLOCK_SECONDS_PER_MINUTE - 1;
                    next            = timer2->minutes - 1;
                    timer2->minutes = next;
                    if ((s8)next < 0) {
                        next = timer2->hours;
                        if (next != 0u) {
                            timer2->minutes = GAME_CLOCK_MINUTES_PER_HOUR - 1;
                            timer2->hours   = next - 1;
                        } else {
                            timer2->minutes = 0;
                            timer2->seconds = 0;
                        }
                    }
                }
            }
        }
    }
}
