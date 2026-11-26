#include "game_00.h"

MATCH bool func_801C2894(s8 tuning_delta) {
    /* FAKE: delta pinned to a2; retail keeps tuning_delta in a0 for block 1. */
    s8 next;

    if (SELF(Actor)->tint.steps.delta.r != 0) {
        next                          = SELF(Actor)->tint.steps.delta.r + tuning_delta;
        SELF(Actor)->tint.bytes.rgb.r = next;
        if (SELF(Actor)->tint.steps.delta.r >= -0x3F) {
            SELF(Actor)->tint.steps.delta.r = -0x40;
        }
    }
    if (SELF(Actor)->tint.steps.delta.g != 0) {
        next                          = SELF(Actor)->tint.steps.delta.g + tuning_delta;
        SELF(Actor)->tint.bytes.rgb.g = next;
        if (SELF(Actor)->tint.steps.delta.g >= -0x3F) {
            SELF(Actor)->tint.steps.delta.g = -0x40;
        }
    }
    if (SELF(Actor)->tint.steps.delta.b != 0) {
        next                          = SELF(Actor)->tint.steps.delta.b + tuning_delta;
        SELF(Actor)->tint.bytes.rgb.b = next;
        if (SELF(Actor)->tint.steps.delta.b >= -0x3F) {
            SELF(Actor)->tint.steps.delta.b = -0x40;
        }
    }
    return (SELF(Actor)->tint.raw & ~0xFF) == 0xC0C0C000;
}
