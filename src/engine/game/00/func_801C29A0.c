#include "game_00.h"

MATCH bool func_801C29A0(s8 tuning_delta) {
    s8  value;
    s16 next;

    value = TASK(Actor)->tint.steps.delta.r;
    if (value != -0x80) {
        next = value - tuning_delta;
        if (next < -0x80) {
            TASK(Actor)->tint.steps.delta.r = -0x80;
        } else {
            TASK(Actor)->tint.steps.delta.r = next;
        }
    }

    value = TASK(Actor)->tint.steps.delta.g;
    if (value != -0x80) {
        next = value - tuning_delta;
        if (next < -0x80) {
            TASK(Actor)->tint.steps.delta.g = -0x80;
        } else {
            TASK(Actor)->tint.steps.delta.g = next;
        }
    }

    value = TASK(Actor)->tint.steps.delta.b;
    if (value != -0x80) {
        next = value - tuning_delta;
        if (next < -0x80) {
            TASK(Actor)->tint.steps.delta.b = -0x80;
        } else {
            TASK(Actor)->tint.steps.delta.b = next;
        }
    }

    return (TASK(Actor)->tint.raw & ~0xFF) == 0x80808000;
}
