#include "game_00.h"

MATCH void func_801C2018(void) {
    s32 selected_record_count;
    s32 kind_10_count;
    s32 record_kind_11;
    s32 record_kind_10;
    s32 counter_threshold;
    s32 record_byte_offset;
    u8* input_bits;
    s32 bit_index;
    u8* status_byte_ptr;
    u8* counter_word;
    u8  record_kind;
    u8  selector_thresholds[10];
    u8* party_state;
    u8* gate_byte_ptr;

    memcpy(selector_thresholds, s_FairyConstructionThresholds, sizeof(selector_thresholds));
    input_bits  = D_8014554C;
    party_state = (u8*)PARTY_STATE_PTR;
    if ((SYS_TestFlag(input_bits, 4U) != 0) && (SYS_TestFlag(input_bits + 3, 4U) == 0) && (party_state[0x54F3] < 30U)) {
        party_state[0x54F3] = (party_state[0x54F3] + 1);
    }
    if (g_SceneState.scenario_id >= 8) {
        bit_index     = 246;
        gate_byte_ptr = &D_801455C3;
        if (*gate_byte_ptr != 0) {
            record_kind_10 = 0xA;
            record_kind_11 = 0xB;
            counter_word   = gate_byte_ptr - 0x1B;
        loop_7:
            /* Retail passes the full s32 selector despite the helpers' u8 prototypes. */
            if (((s32 (*)(void*, s32))SYS_TestFlag)(&g_SceneEventFlags, bit_index) == 0) {
                kind_10_count         = 0;
                selected_record_count = 0;
                for (record_byte_offset = 0; record_byte_offset < 480; record_byte_offset += 8) {
                    if (((u8*)g_FairyJobs)[record_byte_offset] != 0) {
                        record_kind = ((u8*)g_FairyJobs)[record_byte_offset + 1];
                        if (record_kind == record_kind_10) {
                            kind_10_count += 1;
                        } else if (record_kind == record_kind_11) {
                            selected_record_count += 1;
                        }
                    }
                }
                if ((bit_index == 246) || (bit_index == 249) || (bit_index == 252)) {
                    selected_record_count = kind_10_count;
                }
                if ((u8)selected_record_count != 0) {
                    *(u32*)counter_word = (*(u32*)counter_word + 1);
                    if ((bit_index == 246) || (bit_index == 249) || (bit_index == 252)) {
                        counter_threshold = (s8)selector_thresholds[bit_index - 0xF6u] - D_801455C5;
                    } else {
                        counter_threshold = (s8)selector_thresholds[bit_index - 0xF6u] - counter_word[0x1E];
                    }
                    CLAMP_MIN(counter_threshold, 5);
                    if (*(u32*)counter_word >= counter_threshold) {
                        ((void (*)(void*, s32))SYS_SetFlag)(counter_word - 0x680, bit_index);
                        *(u32*)counter_word = 0U;
                    }
                }
            } else {
                bit_index += 1;
                if (bit_index < 256) {
                    /* Retry with the next selector. */
                    goto loop_7;
                }
            }
            status_byte_ptr = &D_801455C4;
            if (*status_byte_ptr < 7U) {
                func_801C1E88(1, (s32*)(status_byte_ptr - 0xC));
            }
            if (*(u8*)(&D_801455C3) < 0xAU) {
                func_801C1E88(0, (s32*)(status_byte_ptr - 8));
            }
            func_801C1F4C(5);
            func_801C1F4C(0xB);
        }
    }
    if ((SYS_TestFlag(g_SceneEventFlags, 245U) == 0) && (D_801455C4 >= 4U)) {
        SYS_SetFlag(g_SceneEventFlags, 245U);
    }
}
