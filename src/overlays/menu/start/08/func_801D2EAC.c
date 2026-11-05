#include "start_08.h"

/* Runs the four-row choice menu: moves the D_801ED618 cursor on up/down, then on confirm advances the menu step by
 * the chosen row, or on cancel backs out to the previous panel. */
MATCH void func_801D2EAC(void) {
    s32 pad;
    u8  cursor;

    Menu_DrawClutStrip(D_80144953);
    D_80148504.kind         = 0;
    D_80148504.group_cursor = 0xFF;
    D_80148624              = 1;
    D_801484EB              = 0xFF;
    D_801484CC              = D_801ED618 + 0x13;
    D_80148628              = D_801484E4 + D_801ED618 * 0x30;
    D_8014862A              = D_801484E6 + 4;
    pad                     = INPUT_GetRepeatedButtons(g_InputPressed & (PADLright | PADLleft));
    cursor                  = D_801ED618;
    if (pad & PADLleft) {
        D_801ED618--;
        if (D_801ED618 < 0) {
            D_801ED618 = 3;
        }
    }
    if (pad & PADLright) {
        D_801ED618++;
        if (D_801ED618 >= 4) {
            D_801ED618 = 0;
        }
    }
    if ((s8)cursor != D_801ED618) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
    if (g_InputPressed & D_80145AC2) {
        D_801484EB = D_801ED618;
        SND_PlayCue(EMI_CUE_ID(1, 4));
        if (D_801ED618 == 1) {
            u8* step = &D_80148651;

            D_80148652 = 0;
            *step += 3;
            return;
        }
        if (D_801ED618 == 3) {
            u8* step = &D_80148651;

            D_80148504.group        = 4;
            D_80148504.group_first  = s_ChoiceMenuValues[4];
            D_80148504.group_cursor = s_ChoiceMenuCursors[4];
            *step += 7;
            return;
        }
        {
            u8*  step         = &D_80148651;
            s32  group        = D_80148504.group;
            s32  group_cursor;
            u8   next;

            next                     = *step;
            D_80148504.group_first   = s_ChoiceMenuValues[group];
            group_cursor             = s_ChoiceMenuCursors[group];
            next                    += 1;
            D_80148504.drawn_cursor  = 0xFF;
            *step                    = next;
            D_80148504.group_cursor  = group_cursor;
            return;
        }
    }
    if (g_InputPressed & D_80145AC4) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        SND_PlayCue(EMI_CUE_ID(1, 2));
        D_801484BF = 1;
        D_801484E3 = 1;
        D_80148507 = 1;
        D_80148624 = 0;
        {
            u8* value = &D_80148654;

            *value += 5;
        }
        D_80148651 += 2;
    }
}
