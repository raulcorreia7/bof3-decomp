#include "game_00.h"

MATCH bool func_801C2894(s8 tuning_delta) {
    /* FAKE: delta pinned to a2; retail keeps tuning_delta in a0 for block 1. */
    s8 next;

    if (g_Task->tint.signed_bytes.unk_5D != 0) {
        next                      = g_Task->tint.signed_bytes.unk_5D + tuning_delta;
        g_Task->tint.bytes.unk_5D = next;
        if (g_Task->tint.signed_bytes.unk_5D >= -0x3F) {
            g_Task->tint.signed_bytes.unk_5D = -0x40;
        }
    }
    if (g_Task->tint.signed_bytes.unk_5E != 0) {
        next                      = g_Task->tint.signed_bytes.unk_5E + tuning_delta;
        g_Task->tint.bytes.unk_5E = next;
        if (g_Task->tint.signed_bytes.unk_5E >= -0x3F) {
            g_Task->tint.signed_bytes.unk_5E = -0x40;
        }
    }
    if (g_Task->tint.signed_bytes.unk_5F != 0) {
        next                      = g_Task->tint.signed_bytes.unk_5F + tuning_delta;
        g_Task->tint.bytes.unk_5F = next;
        if (g_Task->tint.signed_bytes.unk_5F >= -0x3F) {
            g_Task->tint.signed_bytes.unk_5F = -0x40;
        }
    }
    return (g_Task->tint.word & ~0xFF) == 0xC0C0C000;
}
