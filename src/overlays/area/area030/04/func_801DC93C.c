#include "area030_04.h"

/* Runs the area-030 command menu: cursor movement, cancel/confirm buttons, command cycling and the selected
 * page title. */
#ifdef NON_MATCHING
NON_MATCHING void func_801DC93C(void) {
    s32 pad;
    s32 row_mod;
    s32 cmd;
    s8  frame;
    u16 message_id;
    u8  frame_now;
    u8  cursor;
    u8  next;
    u8  target_cmd;
    u8  new_cmd;

    pad = INPUT_REPEATED(g_PadStates[0].pressed, (PADLright | PADLleft));
    if (pad & PADLleft) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        cursor                    = g_SpawnedActors[6].unk_06 - 1;
        g_SpawnedActors[6].unk_06 = cursor;
        if (cursor & 0x80) {
            g_SpawnedActors[6].unk_06 = 2;
        }
    } else if (pad & PADLright) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        next                      = g_SpawnedActors[6].unk_06 + 1;
        g_SpawnedActors[6].unk_06 = next;
        if ((u32)(next & BYTE_MASK) >= 3U) {
            g_SpawnedActors[6].unk_06 = 0;
        }
    } else {
        if (g_InputMasks[FISHING_INPUT_CANCEL] & g_PadStates[0].pressed) {
            SND_SeqFadeIn(0, 0, 0x14, 0x10);
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
            new_cmd = 5;
            if (((u32)(g_SpawnedActors[6].header.mode - 3) < 2U) || (cmd = g_SpawnedActors[6].header.mode & BYTE_MASK, new_cmd = 0xB, (cmd == 8)) || (new_cmd = 0xF, (cmd == 0xE))) {
                g_SpawnedActors[6].header.mode = new_cmd;
            }
            g_SpawnedActors[6].link = 0;
            frame                   = 4;
            goto block_28; /* shared selection join */
        }
        if (g_InputMasks[FISHING_INPUT_CAST] & g_PadStates[0].pressed) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            if (g_SpawnedActors[6].unk_06 == 0) {
                if (g_SpawnedActors[6].header.mode != 8) {
                    if (g_SpawnedActors[6].header.mode == 0xE) {
                        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
                        target_cmd = 0xF;
                        goto block_26; /* shared selection join */
                    }
                } else {
                    goto block_25; /* shared selection join */
                }
            } else if (g_SpawnedActors[6].unk_06 == 1) {
                if ((u32)(g_SpawnedActors[6].header.mode - 3) < 2U) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
                    target_cmd = 5;
                    goto block_26; /* shared selection join */
                }
                if ((g_SpawnedActors[6].header.mode & BYTE_MASK) == 0xE) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
                    target_cmd = 0xF;
                    goto block_26; /* shared selection join */
                }
            } else {
                if ((u32)(g_SpawnedActors[6].header.mode - 3) < 2U) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
                    target_cmd = 5;
                    goto block_26; /* shared selection join */
                }
                if ((g_SpawnedActors[6].header.mode & BYTE_MASK) == 8) {
                block_25:
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
                    target_cmd = 0xB;
                block_26:
                    g_SpawnedActors[6].header.mode = target_cmd;
                }
            }
            frame = TASK(Actor)->unk_03 + 1;
        block_28:
            FIELD(s8, g_Task, 0x3u) = frame;
        }
    }
    frame_now = TASK(Actor)->unk_03;
    if (frame_now == 2) {
        row_mod = g_SpawnedActors[6].unk_06 & 3;
        if (row_mod == 1) {
            message_id = FISHING_MSG_DATA_TITLE;
            goto block_39; /* shared selection join */
        }
        if (row_mod < 2) {
            message_id = FISHING_MESSAGE_EQUIP_ROD_LURE;
            goto block_39; /* shared selection join */
        }
        if (row_mod == frame_now) {
            message_id = FISHING_MESSAGE_HOW_TO_FISH;
        block_39:
            UI_TextDraw(29, 20, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, message_id));
        }
        UI_CursorDraw((g_SpawnedActors[6].unk_06 * 48) + 88, 46U, 0);
    }
}
#else
INCLUDE_ASM(func_801DC93C);
#endif
