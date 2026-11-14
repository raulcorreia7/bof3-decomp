#include "magic060_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EFF44 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EFF88(void) {
    SYS_DISPATCH_BYTE(D_801F0BBC, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F012C();
    }
}

#include "overlays/bmagic/Effect_ClearTimerNextStep.h"

MATCH void func_801F0030(void) {
    u8 count;

    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x10) {
        g_BattleEffectBattler->param.unk_0B = 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0090(void) {
    PartyMember* work;

    work = (PartyMember*)g_BattleEffectBattler;
    if (work->param.unk_0B == 0x83) {
        g_Task->header.step++;
    }
}

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801F012C);

MATCH void func_801F0254(void) {
    SYS_DISPATCH_BYTE(D_801F0BCC, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F0428();
    }
}

MATCH void func_801F02CC(void) {
    if (g_BattleEffectBattler->param.unk_0B == 1) {
        g_Task->unk_09 = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F031C(void) {
    u8 count;

    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x1E) {
        g_BattleEffectBattler->param.unk_0B = 2;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F037C(void) {
    PartyMember* work;

    work = (PartyMember*)g_BattleEffectBattler;
    if (work->param.unk_0B == 0x83) {
        g_Task->header.step++;
    }
}

MATCH void func_801F03BC(void) {
    PartyMember* active;

    g_Task->unk_09 = g_Task->unk_09 - 2;
    if (g_Task->unk_09 == 0) {
        active               = BATTLE_ACTIVE_WORK;
        active->param.unk_0B = active->param.unk_0B - 1;
        func_801E5988();
    }
}

/* Draws the turning grey square at the screen centre: four corners a quarter turn apart
 * on a circle that grows with byte 0x09, shaded by a third of it. */
MATCH void func_801F0428(void) {
    POLY_G4* prim;
    u8       shade;

    GFX_AddDitheredDrawMode(3, getTPage(0, 2, 320, 256));
    prim                             = GFX_BeginPolyG4(1);
    D_1F800000.view.scenario.math_00 = g_Task->unk_09 * 3 + 18;
    D_1F800000.view.scenario.math_08 = ((g_Task->unk_09 + 6) & 0x1F) << 7;
    setXY0(prim, FIXED_MUL(rsin(D_1F800000.view.scenario.math_08), D_1F800000.view.scenario.math_00) + 160, FIXED_MUL(rcos(D_1F800000.view.scenario.math_08), D_1F800000.view.scenario.math_00) + 120);
    D_1F800000.view.scenario.math_08 = ((g_Task->unk_09 + 14) & 0x1F) << 7;
    prim->x1                         = FIXED_MUL(rsin(D_1F800000.view.scenario.math_08), D_1F800000.view.scenario.math_00) + 160;
    prim->y1                         = FIXED_MUL(rcos(D_1F800000.view.scenario.math_08), D_1F800000.view.scenario.math_00) + 120;
    D_1F800000.view.scenario.math_08 = ((g_Task->unk_09 + 30) & 0x1F) << 7;
    prim->x2                         = FIXED_MUL(rsin(D_1F800000.view.scenario.math_08), D_1F800000.view.scenario.math_00) + 160;
    prim->y2                         = FIXED_MUL(rcos(D_1F800000.view.scenario.math_08), D_1F800000.view.scenario.math_00) + 120;
    D_1F800000.view.scenario.math_08 = ((g_Task->unk_09 + 22) & 0x1F) << 7;
    prim->x3                         = FIXED_MUL(rsin(D_1F800000.view.scenario.math_08), D_1F800000.view.scenario.math_00) + 160;
    prim->y3                         = FIXED_MUL(rcos(D_1F800000.view.scenario.math_08), D_1F800000.view.scenario.math_00) + 120;
    shade                            = g_Task->unk_09 / 3;
    D_1F800000.view.scenario.math_04 = shade * 6;
    setRGB0(prim, D_1F800000.view.scenario.math_04, D_1F800000.view.scenario.math_04, D_1F800000.view.scenario.math_04);
    setRGB1(prim, D_1F800000.view.scenario.math_04, D_1F800000.view.scenario.math_04, D_1F800000.view.scenario.math_04);
    setRGB2(prim, D_1F800000.view.scenario.math_04, D_1F800000.view.scenario.math_04, D_1F800000.view.scenario.math_04);
    setRGB3(prim, D_1F800000.view.scenario.math_04, D_1F800000.view.scenario.math_04, D_1F800000.view.scenario.math_04);
    GFX_AddPrim(3, sizeof(POLY_G4));
    GFX_AddDitheredDrawMode(3, getTPage(0, 0, 320, 256));
}

MATCH void func_801F07E8(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectModes + 11, 2, g_Task);
}

MATCH void func_801F082C(void) {
    PartyMember** actor;

    actor = &g_Battle.selected_actor;
    GFX_FreePaletteFadeTarget(*actor);
    g_Task->param.unk_0B = GFX_AllocPaletteFade(*actor, 0, 0, 0, 1);
    g_Task->unk_09       = 0;
    g_Task->header.step += 1;
}

MATCH void func_801F08B8(void) {
    if (g_FrameCount & 1) {
        g_PaletteFades[g_Task->param.unk_0B].offset.red += 1;
        g_PaletteFades[g_Task->param.unk_0B].offset.green += 1;
        g_PaletteFades[g_Task->param.unk_0B].offset.blue += 1;
    }
    if (g_PaletteFades[g_Task->param.unk_0B].offset.red == 8) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801F09E0(void) {
    if (g_FrameCount & 1) {
        g_PaletteFades[g_Task->param.unk_0B].offset.red -= 1;
        g_PaletteFades[g_Task->param.unk_0B].offset.green -= 1;
        g_PaletteFades[g_Task->param.unk_0B].offset.blue -= 1;
    }
    if (g_PaletteFades[g_Task->param.unk_0B].offset.red == 0) {
        g_Task->header.step = 1;
    }
    if (g_BattleEffectBattler->param.unk_0B & 0x80) {
        func_80196718(g_Battle.selected_actor);
        func_800AF814(g_Battle.target_selector);
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}
