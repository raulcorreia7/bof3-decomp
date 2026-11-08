#include "game_00.h"

MATCH bool func_801C29A0(s8 tuning_delta) {
    s8  value;
    s16 next;

    value = g_Task->tint.signed_bytes.unk_5D;
    if (value != -0x80) {
        next = value - tuning_delta;
        if (next < -0x80) {
            g_Task->tint.signed_bytes.unk_5D = -0x80;
        } else {
            g_Task->tint.signed_bytes.unk_5D = next;
        }
    }

    value = g_Task->tint.signed_bytes.unk_5E;
    if (value != -0x80) {
        next = value - tuning_delta;
        if (next < -0x80) {
            g_Task->tint.signed_bytes.unk_5E = -0x80;
        } else {
            g_Task->tint.signed_bytes.unk_5E = next;
        }
    }

    value = g_Task->tint.signed_bytes.unk_5F;
    if (value != -0x80) {
        next = value - tuning_delta;
        if (next < -0x80) {
            g_Task->tint.signed_bytes.unk_5F = -0x80;
        } else {
            g_Task->tint.signed_bytes.unk_5F = next;
        }
    }

    return (g_Task->tint.word & ~0xFF) == 0x80808000;
}
