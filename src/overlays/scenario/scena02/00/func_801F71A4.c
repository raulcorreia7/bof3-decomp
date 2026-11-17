#include "scena02_00.h"
#include "area/map.h"
#include "area/spad.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F71A4(void) {
    /* Retail takes the handler index from the entry $v0; the uninitialised local reads it. */
    u32 index;

    /* FAKE: without the block the scheduler hoists the index shift above the
       ra store (84.46%); the lock restores the retail order (99.85%). */
    FAKE_ORDER_LOCK(D_801FE288[index]());
}

MATCH void func_801F71D8(void) {
    *g_Scenario2Flags = 0;
    g_ScriptVarsWord  = 0;
    D_80146872        = 1;
}

#ifdef NON_MATCHING
NON_MATCHING void func_801F71FC(void) {
    switch (g_SceneState.step_05) {
        case 0:
            Game_ClearScriptActive();
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x20);
            g_SceneState.step_05 = 2;
            break;
        default:
            break;
    }
}
#else
INCLUDE_ASM(func_801F71FC);
#endif

MATCH void func_801F7A60(void) {
    SYS_DISPATCH_BYTE(D_801FE294, g_SceneState.state_04);
}

MATCH void func_801F7A9C(void) {
    if ((SYS_TestFlag(g_SceneFlags, 0x3F) == 0) && (g_GameAreaId == AREA_ID_MCNEIL_MANOR_COURTYARD)) {
        if (SYS_TestFlag(g_SceneFlags, 0x28) != 0) {
            func_801FC044(0);
        }
        if (SYS_TestFlag(g_SceneFlags, 0x29) != 0) {
            func_801FBF94(0);
        }
        if ((SYS_TestFlag(g_SceneFlags, 7) == 0) || (SYS_TestFlag(g_SceneFlags, 0x34) != 0)) {
            if (SYS_TestFlag(g_SceneFlags, 0x2B) != 0) {
                func_801FC0F4(5);
            }
            if (SYS_TestFlag(g_SceneFlags, 0x2C) != 0) {
                func_801FC1A4(5);
            }
        }
        func_801FC25C(1);
        func_801FC308(2);
        func_801FC518(3);
        func_801FC5D0(4);
        if ((SYS_TestFlag(g_SceneFlags, 7) == 0) || (SYS_TestFlag(g_SceneFlags, 0x34) != 0)) {
            func_801FC3B4(6);
            func_801FC46C(7);
            func_801FC688(8);
        }
        if (SYS_TestFlag(g_SceneFlags, 0x2E) == 0) {
            func_801FC734(9);
            func_801FC7E4();
            return;
        }
        func_801FC9CC();
    }
}

MATCH void func_801F7C30(void) {
}
