#include "start_08.h"

extern u8 D_80148656;

MATCH void func_801D3174(void) {
    u8* base;
    u8  mode;
    u8* step;
    u8* row;
    u8* pair;
    s32 trigger;
    u8  old_cursor;
    s8  step_down;
    u8  step_up;
    u8  entry;
    u8  counter;
    u8  saved;
    u8* count;
    s32 result;
    s32 offset;
    u16 pad;

    Menu_DrawClutStrip(D_80144953);
    step = &D_8014850C;
    mode = 3;
    if (D_801ED618 == 0) {
        mode = 1;
    }
    *step = mode;
    base  = step;
    base -= 8;
    D_801484CC = Item_GetDescription(D_8014850E, D_801C893C[D_8014850E][D_80148510]);
    pad        = g_InputPressed;
    /* FAKE: keeps the pad load ahead of the panel stores. */
    MATCH_BARRIER();
    D_80148624 = 1;
    D_80148628 = (u16)D_80148508 + 7;
    offset     = (D_80148510 - D_8014850F) * 13 + 0x1A;
    D_8014862A = (u16)D_8014850A + offset;
    trigger    = INPUT_REPEATED(pad, (INPUT_DIRECTIONAL | PADL1 | PADR1));
    if (trigger & PADLleft) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
        D_80148514                      = 0x32;
        s_ChoiceMenuCursors[D_8014850E] = D_80148510;
        s_ChoiceMenuValues[D_8014850E]  = D_8014850F;
        step_down                       = D_8014850E - 1;
        D_8014850E                      = step_down;
        if (step_down < 0) {
            D_8014850E = 3;
        }
        /* Both step directions converge on the shared reload block. */
        goto store_selection;
    }
    if (trigger & PADLright) {
        D_80148514 = 0x31;
        SND_PlayCue(EMI_CUE_ID(1, 1));
        s_ChoiceMenuCursors[D_8014850E] = D_80148510;
        s_ChoiceMenuValues[D_8014850E]  = D_8014850F;
        step_up                         = D_8014850E + 1;
        D_8014850E                      = step_up;
        if ((u32)(step_up & BYTE_MASK) >= 4U) {
            D_8014850E = 0;
        }
    /* Shared tail of both cursor-step directions. */
    store_selection:
        D_80148510 = s_ChoiceMenuCursors[D_8014850E];
        D_8014850F = s_ChoiceMenuValues[D_8014850E];
        return;
    }
    old_cursor = D_80148510;
    if (trigger & PADLup) {
        if (old_cursor != 0) {
            D_80148510 = old_cursor - 1;
        }
        if (D_80148510 < D_8014850F) {
            D_80148516 = 0xF0;
        }
    } else if (trigger & PADLdown) {
        if (old_cursor < 0x7F) {
            D_80148510 = old_cursor + 1;
        }
        if (D_80148510 >= D_8014850F + 9) {
            D_80148516 = 0x10;
        }
    } else if (trigger & 4) {
        u8 group = D_8014850F;
        if (group == 0) {
            D_80148510 = 0;
        } else if (group < 9) {
            D_80148510 = old_cursor - group;
            D_8014850F = 0;
        } else {
            D_80148510 = old_cursor - 9;
            D_8014850F = group - 9;
        }
    } else if (trigger & 8) {
        u8 group = D_8014850F;
        if (group == 0x77) {
            D_80148510 = 0x7F;
        } else if (group >= 0x6F) {
            D_80148510 = old_cursor + (0x77 - group);
            D_8014850F = 0x77;
        } else {
            D_80148510 = old_cursor + 9;
            D_8014850F = group + 9;
        }
    }
    s_ChoiceMenuCursors[base[0xA]] = base[0xC];
    s_ChoiceMenuValues[base[0xA]]  = base[0xB];
    if (old_cursor != base[0xC]) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
    }
    row  = D_801C893C[base[0xA]] + base[0xC];
    pair = D_801C8950[base[0xA]] + base[0xC];
    if (*(s16*)(base + 0x12) != 0) {
        return;
    }
    if (g_InputPressed & D_80145AC2) {
        if (*row != 0) {
            SND_PlayCue(EMI_CUE_ID(1, 3));
            if (D_801ED618 == 0) {
                if ((func_801AF494(base[8], 0, base[0xA], *row) & BYTE_MASK) != 0) {
                    entry = *row;
                    if (D_801C8970[entry * 0x12] & 0x10) {
                        result = func_801E8C9C(0, entry, 0) & BYTE_MASK;
                        if (result == 0 || result == 4) {
                            SND_PlayCue(EMI_CUE_ID(1, 4));
                            if (TIMER_EXPIRED(*pair)) {
                                *row = 0;
                            }
                        } else {
                            /* Result outside the accepted set reports failure. */
                            goto fail;
                        }
                    } else {
                        saved      = base[0xC];
                        D_80148656 = 0;
                        D_80148624 = 0;
                        counter    = D_80148651 + 4;
                        /* Both success arms converge on the commit block. */
                        goto commit;
                    }
                } else {
                    /* The confirm call rejected the selection. */
                    goto fail;
                }
            } else {
                if ((func_801AF494(base[8], 0, base[0xA], D_801C893C[base[0xA]][base[0xC]]) & BYTE_MASK) != 0) {
                    saved      = base[0xC];
                    D_8014865B = 0;
                    counter    = D_80148651 + 3;
                /* Shared tail of both selection-commit arms. */
                commit:
                    base[0xD]  = saved;
                    D_80148651 = counter;
                    return;
                }
                /* The row has no selectable entry. */
                goto fail;
            }
        } else {
        /* Failure path of the confirm mask queues the error cue. */
        fail:
            SND_PlayCue(EMI_CUE_ID(1, 7));
        }
    } else if (g_InputPressed & D_80145AC4) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        count = &D_80148651;
        *count -= 1;
    }
}
