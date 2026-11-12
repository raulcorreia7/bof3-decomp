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

INCLUDE_ASM(func_801F0428);

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
