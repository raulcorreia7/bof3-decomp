#include "game_00.h"

MATCH void func_80198CAC(void) {
    GameClock* clock;
    GameClock* timer1;
    GameClock* timer2;
    u8         next;
    u8         hours;

    if (g_GameStateIndex != GAME_REQUEST_SCENE_CAMERA) {
        clock = &g_SaveData.play_clock;
        if ((*(volatile u32*)clock & 0xFFFFFFu) != GAME_CLOCK_STOPPED) {
            if (++clock->thirtieths_03 >= GAME_CLOCK_THIRTIETHS_PER_SECOND) {
                clock->thirtieths_03 = 0;
                if (++clock->seconds_02 >= GAME_CLOCK_SECONDS_PER_MINUTE) {
                    clock->seconds_02 = 0;
                    if (++clock->minutes_01 >= GAME_CLOCK_MINUTES_PER_HOUR) {
                        hours = clock->hours_00;
                        if (hours < GAME_CLOCK_MAX_HOURS) {
                            clock->minutes_01 = 0;
                            clock->hours_00   = hours + 1;
                        } else {
                            clock->minutes_01 = 0x3B;
                            clock->seconds_02 = 0x3B;
                        }
                    }
                }
            }
        }
        timer1 = &g_SaveData.celerity_timer;
        if (*(volatile u32*)timer1 != 0u) {
            next                  = timer1->thirtieths_03 - 1;
            timer1->thirtieths_03 = next;
            if ((s8)next < 0) {
                timer1->thirtieths_03 = 0x1D;
                next                  = timer1->seconds_02 - 1;
                timer1->seconds_02    = next;
                if ((s8)next < 0) {
                    timer1->seconds_02 = 0x3B;
                    next               = timer1->minutes_01 - 1;
                    timer1->minutes_01 = next;
                    if ((s8)next < 0) {
                        next = timer1->hours_00;
                        if (next != 0u) {
                            timer1->minutes_01 = 0x3B;
                            timer1->hours_00   = next - 1;
                        } else {
                            timer1->minutes_01 = 0;
                            timer1->seconds_02 = 0;
                        }
                    }
                }
            }
        }
        timer2 = &g_SaveData.bonebreak_timer;
        if (*(volatile u32*)timer2 != 0u) {
            next                  = timer2->thirtieths_03 - 1;
            timer2->thirtieths_03 = next;
            if ((s8)next < 0) {
                timer2->thirtieths_03 = 0x1D;
                next                  = timer2->seconds_02 - 1;
                timer2->seconds_02    = next;
                if ((s8)next < 0) {
                    timer2->seconds_02 = 0x3B;
                    next               = timer2->minutes_01 - 1;
                    timer2->minutes_01 = next;
                    if ((s8)next < 0) {
                        next = timer2->hours_00;
                        if (next != 0u) {
                            timer2->minutes_01 = 0x3B;
                            timer2->hours_00   = next - 1;
                        } else {
                            timer2->minutes_01 = 0;
                            timer2->seconds_02 = 0;
                        }
                    }
                }
            }
        }
    }
}
