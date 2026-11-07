#include "area030_04.h"

/* Runs the area-030 command menu: cursor movement, cancel/confirm buttons, command cycling and the selected
 * page color. */
/* nonmatching unmeasured: tried opcode@+0x0: entry pad/color selection block and the command-cycle switch do not
 * reproduce the retail prologue and case layout; menu logic is in place. resume: rebuild the switch as the retail case
 * 0/1/default order and re-check the pad mask split. */
#ifdef NON_MATCHING
NON_MATCHING void func_801DC93C(void) {
    s32 pad;
    s32 row_mod;
    s32 cmd;
    s8  frame;
    u16 color;
    u8  frame_now;
    u8  cursor;
    u8  next;
    u8  target_cmd;
    u8  new_cmd;

    pad = INPUT_REPEATED(g_InputPressed, (PADLright | PADLleft));
    if (pad & PADLleft) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
        cursor     = D_80144286 - 1;
        D_80144286 = cursor;
        if (cursor & 0x80) {
            D_80144286 = 2;
        }
    } else if (pad & PADLright) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
        next       = D_80144286 + 1;
        D_80144286 = next;
        if ((u32)(next & BYTE_MASK) >= 3U) {
            D_80144286 = 0;
        }
    } else {
        if (g_InputMasks[FISHING_INPUT_CANCEL] & g_InputPressed) {
            SND_FadeInSequence(0, 0, 0x14, 0x10);
            SND_PlayCue(EMI_CUE_ID(1, 6));
            new_cmd = 5;
            if (((u32)(D_80144281 - 3) < 2U) || (cmd = D_80144281 & BYTE_MASK, new_cmd = 0xB, (cmd == 8)) ||
                (new_cmd = 0xF, (cmd == 0xE))) {
                D_80144281 = new_cmd;
            }
            D_8014428B = 0;
            frame      = 4;
            goto block_28; /* shared selection join */
        }
        if (g_InputMasks[FISHING_INPUT_CAST] & g_InputPressed) {
            SND_PlayCue(EMI_CUE_ID(1, 3));
            if (D_80144286 == 0) {
                if (D_80144281 != 8) {
                    if (D_80144281 == 0xE) {
                        SND_PlayCue(EMI_CUE_ID(1, 2));
                        target_cmd = 0xF;
                        goto block_26; /* shared selection join */
                    }
                } else {
                    goto block_25; /* shared selection join */
                }
            } else if (D_80144286 == 1) {
                if ((u32)(D_80144281 - 3) < 2U) {
                    SND_PlayCue(EMI_CUE_ID(1, 2));
                    target_cmd = 5;
                    goto block_26; /* shared selection join */
                }
                if ((D_80144281 & BYTE_MASK) == 0xE) {
                    SND_PlayCue(EMI_CUE_ID(1, 2));
                    target_cmd = 0xF;
                    goto block_26; /* shared selection join */
                }
            } else {
                if ((u32)(D_80144281 - 3) < 2U) {
                    SND_PlayCue(EMI_CUE_ID(1, 2));
                    target_cmd = 5;
                    goto block_26; /* shared selection join */
                }
                if ((D_80144281 & BYTE_MASK) == 8) {
                block_25:
                    SND_PlayCue(EMI_CUE_ID(1, 2));
                    target_cmd = 0xB;
                block_26:
                    D_80144281 = target_cmd;
                }
            }
            frame = g_Task->unk_03 + 1;
        block_28:
            FIELD(s8, g_Task, 0x3u) = frame;
        }
    }
    frame_now = g_Task->unk_03;
    if (frame_now == 2) {
        row_mod = D_80144286 & 3;
        switch (row_mod) { /* irregular */
            default:
                if (row_mod != frame_now) {
                } else {
                    color = D_800100DE;
                block_39:
                    UI_DrawText(0x1D, 0x14, 0, 0xFFU, color + FISHING_TEXT_BANK);
                }
                break;
            case 0:
                color = D_800100A0;
                goto block_39; /* shared selection join */
            case 1:
                color = D_800100C0;
                goto block_39; /* shared selection join */
        }
        Menu_DrawCursorSprite((D_80144286 * 0x30) + 0x58, 0x2EU, 0);
    }
}
#else
INCLUDE_ASM(func_801DC93C);
#endif
