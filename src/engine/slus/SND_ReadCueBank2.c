#include "engine/slus/slus.h"

/* Bank 2's cue reader: loads cue D_8018B404 of the bank into voice slot 0,
 * fills one more slot per layer on the next voices (wrapping at 24), then lets
 * an alias bank supply the tone and voice. */
/* func_8015F5C8 */
MATCH void SND_ReadCueBank2(void) {
    s32 cue;
    s16 program;
    s16 tone;
    s16 voice;

    D_8018B30C = 2;
    cue        = D_8018B404 * 4;
    D_8018B3E0 = D_80148798[cue];
    program    = D_80148798[cue + 1] & EMI_CUE_PROGRAM_MASK;
    D_8018B308 = program;
    D_8018B3F4 = D_80148798[cue + 1] & EMI_CUE_USE_CUE_VOLUME_FLAG;
    tone       = D_80148798[cue + 2] >> 4;
    D_8018B310 = tone;
    D_8018B3E8 = D_80148798[cue + 2] & EMI_CUE_COMPARE_MASK;
    D_8018B40C = g_VabProgramOffsets[program] + VAB_TONE_TABLE + g_VabToneOffsets[tone];
    D_8018B314 = CUE_TONE(D_80148A20)->min;
    D_8018B320 = CUE_TONE(D_80148A20)->shift;
    D_8018B32C = CUE_TONE(D_80148A20)->pan;
    D_8018B324 = CUE_TONE(D_80148A20)->vol;
    D_8018B328 = CUE_TONE(D_80148A20)->vol;
    voice      = D_80148798[cue + 3] & EMI_CUE_VOICE_MASK;
    D_8018B318 = voice;
    D_8018B3E4 = D_80148798[cue + 3] & EMI_CUE_LAYER_MASK;
    if (D_8018B3E4 != 0) {
        D_8018B3E4 = D_8018B3E4 >> 5;
        switch (D_8018B3E4) {
            case 3:
                D_8018B380 = D_80148798[D_8018B404 * 4 + 1] & EMI_CUE_PROGRAM_MASK;
                D_8018B388 = D_8018B310 + D_8018B3E4;
                D_8018B38C = D_8018B314;
                D_8018B398 = D_8018B320;
                D_8018B40C = g_VabProgramOffsets[D_8018B380] + VAB_TONE_TABLE + g_VabToneOffsets[D_8018B388];
                D_8018B39C = CUE_TONE(D_80148A20)->vol;
                D_8018B3A0 = CUE_TONE(D_80148A20)->vol;
                D_8018B3A4 = CUE_TONE(D_80148A20)->pan;
                D_8018B390 = D_8018B318 + 3;
                if (D_8018B390 >= 24) {
                    D_8018B390 = D_8018B318 + 3 - 24;
                }
            case 2:
                D_8018B358 = D_80148798[D_8018B404 * 4 + 1] & EMI_CUE_PROGRAM_MASK;
                D_8018B360 = D_8018B310 + D_8018B3E4;
                D_8018B364 = D_8018B314;
                D_8018B370 = D_8018B320;
                D_8018B40C = g_VabProgramOffsets[D_8018B358] + VAB_TONE_TABLE + g_VabToneOffsets[D_8018B360];
                D_8018B374 = CUE_TONE(D_80148A20)->vol;
                D_8018B378 = CUE_TONE(D_80148A20)->vol;
                D_8018B37C = CUE_TONE(D_80148A20)->pan;
                D_8018B368 = D_8018B318 + 2;
                if (D_8018B368 >= 24) {
                    D_8018B368 = D_8018B318 + 2 - 24;
                }
            case 1:
                D_8018B330 = D_80148798[D_8018B404 * 4 + 1] & EMI_CUE_PROGRAM_MASK;
                D_8018B338 = D_8018B310 + D_8018B3E4;
                D_8018B33C = D_8018B314;
                D_8018B348 = D_8018B320;
                D_8018B40C = g_VabProgramOffsets[D_8018B330] + VAB_TONE_TABLE + g_VabToneOffsets[D_8018B338];
                D_8018B34C = CUE_TONE(D_80148A20)->vol;
                D_8018B350 = CUE_TONE(D_80148A20)->vol;
                D_8018B354 = CUE_TONE(D_80148A20)->pan;
                D_8018B340 = D_8018B318 + 1;
                if (D_8018B340 >= 24) {
                    D_8018B340 = D_8018B318 + 1 - 24;
                }
                break;
        }
    }
    if (D_8018B3E0 != 0) {
        D_8018B30C = D_8018B3E0 & EMI_CUE_ALIAS_MASK;
        switch (D_8018B30C) {
            case 1:
                D_8018B314 = CUE_TONE(D_80148A1C)->min;
                D_8018B320 = CUE_TONE(D_80148A1C)->shift;
                D_8018B32C = CUE_TONE(D_80148A1C)->pan;
                D_8018B324 = CUE_TONE(D_80148A1C)->vol;
                D_8018B328 = CUE_TONE(D_80148A1C)->vol;
                D_8018B318 = D_8014871C[D_8018B404 * 4 + 3];
                break;
            case 3:
                D_8018B314 = CUE_TONE(D_80148A24)->min;
                D_8018B320 = CUE_TONE(D_80148A24)->shift;
                D_8018B32C = CUE_TONE(D_80148A24)->pan;
                D_8018B324 = CUE_TONE(D_80148A24)->vol;
                D_8018B328 = CUE_TONE(D_80148A24)->vol;
                D_8018B318 = D_80148814[D_8018B404 * 4 + 3];
                break;
            case 4:
                D_8018B314 = CUE_TONE(D_80148A28)->min;
                D_8018B320 = CUE_TONE(D_80148A28)->shift;
                D_8018B32C = CUE_TONE(D_80148A28)->pan;
                D_8018B324 = CUE_TONE(D_80148A28)->vol;
                D_8018B328 = CUE_TONE(D_80148A28)->vol;
                D_8018B318 = D_80148890[D_8018B404 * 4 + 3];
                break;
        }
    }
}
