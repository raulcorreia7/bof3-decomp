#include "battle_03.h"

/* This module draws digit glyphs at signed y coordinates. */

/* Queued-slot fields driving the rolling digit display. */
typedef struct {
    u8  pad_00[0x0A];
    s8  digit;
    u8  pad_0b[0x27];
    s16 count;
    u8  pad_34[2];
    u16 x;
    u8  pad_38[2];
    s16 y;
} BattleDigitRoll;

MATCH void Battle_DrawRollingDigits(u8 palette) {
    BattleDigitRoll* view;
    BattleDigitRoll* loop_view;
    s16              counter;
    s16              current_digit;
    s8               digit_index;

    view        = (BattleDigitRoll*)D_801EC2E0;
    counter     = (view->count + 1);
    view->count = counter % 10;

    if ((digit_index = view->digit) >= 0) {
        do {
            loop_view     = (BattleDigitRoll*)D_801EC2E0;
            current_digit = loop_view->count;
            Battle_DrawNumber((loop_view->x - digit_index * 8 - 12), loop_view->y, palette, ((current_digit + digit_index) % 10));
        } while (--digit_index >= 0);
    }
}
