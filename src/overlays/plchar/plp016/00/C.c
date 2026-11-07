#include "plp016_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE404(void) {
    D_801D0630[TASK_BYTES[2]]();
}

INCLUDE_ASM(func_801CE448);

#include "overlays/plchar/func_801CE628.h"

MATCH void func_801CE72C(void) {
    SYS_DISPATCH_TASK(D_801D063C, 2, g_Task);
}

#include "overlays/plchar/func_801CE770.h"

INCLUDE_ASM(func_801CEA94);

#include "overlays/plchar/Char_AdvanceScript.h"

INCLUDE_ASM(func_801CED1C);

#include "overlays/plchar/Char_SpawnActor.h"

#include "overlays/plchar/Char_ProbeFacingCell.h"

MATCH void func_801CF12C(void) {
    SYS_DISPATCH_TASK(D_801D0648, 2, g_Task);
}

#include "overlays/plchar/Char_StartTurn.h"

#include "overlays/plchar/Char_RunStepScript.h"

MATCH void func_801CF338(void) {
    SYS_DISPATCH_TASK(D_801D0654, 2, g_Task);
}

INCLUDE_ASM(func_801CF37C);

#include "overlays/plchar/Char_ClearModeIfSlotFree.h"

MATCH void func_801CF500(void) {
    SYS_DISPATCH_TASK(D_801D065C, 2, g_Task);
}

/* This copy turns between facings 3 and 5; the image's own are the header's. */
MATCH void Char_StartTurn_801CF544(void) {
    CHAR_START_TURN(3, 5);
}

/* The second route step script in this image turns between directions 3 and 5. */
MATCH void Char_RunStepScript_801CF610(void) {
    CHAR_RUN_STEP_SCRIPT(3, 5);
}

MATCH void func_801CF70C(void) {
    func_8014D978();
}

MATCH void func_801CF72C(void) {
    SYS_DISPATCH_TASK(D_801D0668, 2, g_Task);
}

MATCH void func_801CF770(void) {
    SYS_DISPATCH_TASK(D_801D0670, 3, g_Task);
}

#include "overlays/plchar/Char_FaceFreeDirection.h"

INCLUDE_ASM(func_801CF8B4);

#include "overlays/plchar/Char_AdvancePaletteScript.h"

#include "overlays/plchar/Char_StartFacingScript.h"

#include "overlays/plchar/Char_ClearSlotRefIfUnused.h"

MATCH s32 func_801CFD24(s16 x, s16 y) {
    s32 cell;
    s32 i;
    u32 roll;
    u8* record;

    cell = Area_GetCellCode(x, y);
    if ((u8)(cell + 0x10) < 2 || (cell & BYTE_MASK) == 0xF4) {
        func_801CFF30(0, x, y, cell & BYTE_MASK);
        if ((rand() & 7) >= 6) {
            func_801CFF30(4, x, y, cell & BYTE_MASK);
        }
        SND_PlayCue(0x10B);
        return 1;
    }
    if ((u8)(cell + 0xA) < 2) {
        func_801CFF30(0, x, y, cell & BYTE_MASK);
        SND_PlayCue(0x10B);
        roll = rand() & 0xF;
        if (roll < 7) {
            func_801CFF30(3, x, y, cell & BYTE_MASK);
            record = Item_GetRecord(ITEM_CAT_ITEM, 0x29);
            for (i = 0; i < 12; i++) {
                g_TextVariables[0][i] = record[i];
            }
            D_801490E4[0] = 0;
            if (Item_Add(ITEM_CAT_ITEM, 0x29, 1, 0) & BYTE_MASK) {
                SND_PlayCue(0x106);
                Resource_RequestArea(2);
            } else {
                Resource_RequestArea(3);
            }
            g_Task->param.unk_0B = 2;
        } else if (roll >= 12) {
            func_801CFF30(2, x, y, cell & BYTE_MASK);
            func_801C308C(0);
            Char_LoseHP(1, g_GameState->leader_id);
            Resource_RequestArea(0xD9);
            g_GameStateIndex     = 2;
            g_Task->param.unk_0B = 1;
        }
        g_GameStateIndex = 2;
        return 1;
    }
    return 0;
}

/* Exact draft: pin y to s4 and kind to s2, leave x unpinned; shared twins need an evidenced name. */
/* blocker: shared flag lifetime; first diff: +0x04. */
INCLUDE_ASM(func_801CFF30);

MATCH void func_801D001C(void) {
    SYS_DISPATCH_TASK(D_801D0684, 3, g_Task);
}

MATCH void func_801D0060(void) {
    func_801D0444();
    Actor_RequestScript((g_Task->direction_08 - 1) / 2 + 0x42);
    g_Task->unk_0A = 0xB;
    g_Task->unk_03 = 1;
}

INCLUDE_ASM(func_801D00CC);

#include "overlays/plchar/Char_ClearModeIfUnused.h"

INCLUDE_ASM(func_801D02A0);

INCLUDE_ASM(func_801D0444);

MATCH void func_801D05A8(void) {
    D_801D0690[g_Task->unk_2C]();
}

MATCH void func_801D05EC(void) {
    D_801D069C[g_Task->unk_2C]();
}
