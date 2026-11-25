#include "commu02_08.h"
#include "game/spawn.h"
#include "menu/save_data.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
/* The price row: the three digit cells, the row cursor, and the confirm and cancel steps.
 * The split row starts after the bin that holds the function's head. */
NON_MATCHING void func_801D0F88(void) {
    u16 input;
    s32 price;
    s32 clamped;
    s8  rest;

    g_ScratchPad.cells.bytes[2] = (s8)D_801DB07C / 100;
    rest                        = (s8)D_801DB07C % 100;
    g_ScratchPad.cells.bytes[1] = rest / 10;
    g_ScratchPad.cells.bytes[0] = rest % 10;

    input = INPUT_REPEATED(g_PadStates[0].pressed, INPUT_DIRECTIONAL);
    if (input == 0) {
        goto confirm;
    }
    SND_SEPlay(0x100);
    if (input & PADLleft) {
        D_801DB0B4 += 1;
        if ((s8)D_801DB0B4 >= 3) {
            D_801DB0B4 = 0;
        }
    } else if (input & PADLright) {
        D_801DB0B4 -= 1;
        if ((s8)D_801DB0B4 < 0) {
            D_801DB0B4 = 2;
        }
    } else if (input & PADLdown) {
        g_ScratchPad.cells.bytes[(s8)D_801DB0B4] -= 1;
        if ((s8)g_ScratchPad.cells.bytes[(s8)D_801DB0B4] < 0) {
            g_ScratchPad.cells.bytes[(s8)D_801DB0B4] = 9;
        }
    } else if (input & PADLup) {
        g_ScratchPad.cells.bytes[(s8)D_801DB0B4] += 1;
        if ((s8)g_ScratchPad.cells.bytes[(s8)D_801DB0B4] >= 10) {
            g_ScratchPad.cells.bytes[(s8)D_801DB0B4] = 0;
        }
    }

    price      = (s8)g_ScratchPad.cells.bytes[2] * 100 + (s8)g_ScratchPad.cells.bytes[1] * 10 + (s8)g_ScratchPad.cells.bytes[0];
    D_801DB07C = price;
    clamped    = price < 0 ? 0 : price > 100 ? 100 : price;
    D_801DB07C = clamped;
    if (g_Zenny < (u32)clamped) {
        D_801DB07C = (s16)g_Zenny;
    }
    goto draw;

confirm:
    if (g_PadStates[0].pressed & g_InputMasks[INPUT_SLOT_CONFIRM]) {
        SND_SEPlay(0x102);
        if (D_801DB07C != 0) {
            D_801DB0C4 = 4;
            SND_SEPlay(0x104);
            g_SaveData.zenny -= D_801DB07C;
            D_801F294E += 1;
            goto draw;
        }
    } else if ((g_PadStates[0].pressed & g_InputMasks[INPUT_SLOT_CANCEL]) == 0) {
        goto draw;
    } else {
        SND_SEPlay(0x102);
    }
    D_801DB0C4 = 0;
    D_801F294E += 2;

draw:
    if (D_801F294C == 1 && D_801F294D == 2) {
        func_801D3184(0x6E, 0x48);
        func_801D32A0(0x6E, 0x74, (u8)(D_801DB0B4 + 1));
        func_801D2E60(0xB4 - (s8)D_801DB0B4 * 8, 0x99);
    }
}
#else
INCLUDE_ASM(func_801D0F88);
#endif
