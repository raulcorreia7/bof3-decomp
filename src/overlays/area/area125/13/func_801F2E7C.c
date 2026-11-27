#include "area125_13.h"

MATCH void func_801F2E7C(void) {
    s16 screen_x;
    s16 screen_y;

    screen_x = SELF(Actor)->screen_x;
    if (screen_x < 420) {
        if (screen_x < 60) {
            D_801F3834 = 0;
        } else if (screen_x < 180) {
            D_801F3834 = 1;
        } else if (screen_x < 300) {
            D_801F3834 = 2;
        } else if (screen_x < 360) {
            D_801F3834 = 3;
        } else {
            D_801F3834 = 4;
        }
        screen_y = SELF(Actor)->screen_y;
        if (screen_y == 0) {
            func_801F3268(D_801F36F0[D_801F3834]);
            SELF(Actor)->screen_y = D_801F36F8[D_801F3834];
        } else {
            SELF(Actor)->screen_y = screen_y - 1;
        }
        SELF(Actor)->screen_x++;
    } else {
        SELF(Actor)->header.mode++;
    }
    func_801F33B0();
}
