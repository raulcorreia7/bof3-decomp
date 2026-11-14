#include "game_00.h"

MATCH bool func_801C2894(s8 tuning_delta) {
    /* FAKE: delta pinned to a2; retail keeps tuning_delta in a0 for block 1. */
    s8 next;

    if (g_Task->tint.signed_bytes.delta.red != 0) {
        next                       = g_Task->tint.signed_bytes.delta.red + tuning_delta;
        g_Task->tint.bytes.rgb.red = next;
        if (g_Task->tint.signed_bytes.delta.red >= -0x3F) {
            g_Task->tint.signed_bytes.delta.red = -0x40;
        }
    }
    if (g_Task->tint.signed_bytes.delta.green != 0) {
        next                         = g_Task->tint.signed_bytes.delta.green + tuning_delta;
        g_Task->tint.bytes.rgb.green = next;
        if (g_Task->tint.signed_bytes.delta.green >= -0x3F) {
            g_Task->tint.signed_bytes.delta.green = -0x40;
        }
    }
    if (g_Task->tint.signed_bytes.delta.blue != 0) {
        next                        = g_Task->tint.signed_bytes.delta.blue + tuning_delta;
        g_Task->tint.bytes.rgb.blue = next;
        if (g_Task->tint.signed_bytes.delta.blue >= -0x3F) {
            g_Task->tint.signed_bytes.delta.blue = -0x40;
        }
    }
    return (g_Task->tint.word & ~0xFF) == 0xC0C0C000;
}
