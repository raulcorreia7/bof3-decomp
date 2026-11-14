#include "game_00.h"

MATCH bool func_801C29A0(s8 tuning_delta) {
    s8  value;
    s16 next;

    value = g_Task->tint.signed_bytes.delta.red;
    if (value != -0x80) {
        next = value - tuning_delta;
        if (next < -0x80) {
            g_Task->tint.signed_bytes.delta.red = -0x80;
        } else {
            g_Task->tint.signed_bytes.delta.red = next;
        }
    }

    value = g_Task->tint.signed_bytes.delta.green;
    if (value != -0x80) {
        next = value - tuning_delta;
        if (next < -0x80) {
            g_Task->tint.signed_bytes.delta.green = -0x80;
        } else {
            g_Task->tint.signed_bytes.delta.green = next;
        }
    }

    value = g_Task->tint.signed_bytes.delta.blue;
    if (value != -0x80) {
        next = value - tuning_delta;
        if (next < -0x80) {
            g_Task->tint.signed_bytes.delta.blue = -0x80;
        } else {
            g_Task->tint.signed_bytes.delta.blue = next;
        }
    }

    return (g_Task->tint.word & ~0xFF) == 0x80808000;
}
