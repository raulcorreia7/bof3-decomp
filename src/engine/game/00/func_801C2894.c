#include "game_00.h"

MATCH bool func_801C2894(s8 tuning_delta) {
    /* FAKE: delta pinned to a2; retail keeps tuning_delta in a0 for block 1. */
    s8 next;

    if (g_Task->tint.signed_bytes.delta.r != 0) {
        next                     = g_Task->tint.signed_bytes.delta.r + tuning_delta;
        g_Task->tint.bytes.rgb.r = next;
        if (g_Task->tint.signed_bytes.delta.r >= -0x3F) {
            g_Task->tint.signed_bytes.delta.r = -0x40;
        }
    }
    if (g_Task->tint.signed_bytes.delta.g != 0) {
        next                     = g_Task->tint.signed_bytes.delta.g + tuning_delta;
        g_Task->tint.bytes.rgb.g = next;
        if (g_Task->tint.signed_bytes.delta.g >= -0x3F) {
            g_Task->tint.signed_bytes.delta.g = -0x40;
        }
    }
    if (g_Task->tint.signed_bytes.delta.b != 0) {
        next                     = g_Task->tint.signed_bytes.delta.b + tuning_delta;
        g_Task->tint.bytes.rgb.b = next;
        if (g_Task->tint.signed_bytes.delta.b >= -0x3F) {
            g_Task->tint.signed_bytes.delta.b = -0x40;
        }
    }
    return (g_Task->tint.word & ~0xFF) == 0xC0C0C000;
}
