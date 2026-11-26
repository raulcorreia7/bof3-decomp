#include "magic052_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

MATCH void func_801EEC7C(void) {
    PartyMember* work;

    TASK(PartyMember)->unk_09 = 8;
    TASK(PartyMember)->timer  = 4;
    work                      = TASK(PartyMember);
    work->header.mode         = work->header.mode + 1;
}

MATCH void func_801EECBC(void) {
    PartyMember* target;
    u8           index;
    s32          x;

    if (TASK(PartyMember)->timer-- != 0) {
        return;
    }

    index                               = Battle_AllocEffect(1, 80) & BYTE_MASK;
    target                              = TASK(PartyMember);
    g_BattleEffects[index].header.mode  = 0;
    g_BattleEffects[index].header.step  = 0;
    g_BattleEffects[index].target.party = target;
    rand();
    x                                 = g_Battle.selected_actor->screen_x.signed_value + (rand() & 0xF);
    g_BattleEffects[index].screen_x   = x;
    g_BattleEffects[index].screen_y   = g_Battle.selected_actor->screen_y.value - (rand() & 0x1F);
    g_BattleEffects[index].depth      = g_Battle.selected_actor->depth;
    g_BattleEffects[index].arg.unk_09 = TASK(PartyMember)->unk_09;
    if (TASK(PartyMember)->unk_09-- != 0) {
        TASK(PartyMember)->timer = 8;
    } else {
        TASK(PartyMember)->timer = 0x2D;
        TASK(PartyMember)->header.mode++;
    }
}

MATCH void func_801EEE30(void) {
    if (TASK(PartyMember)->timer-- == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
    }
}

MATCH void func_801EEE94(void) {
    Callback handlers[2];

    handlers[0] = func_801EEEE0;
    handlers[TASK(PartyMember)->header.mode]();
}

MATCH void func_801EEEE0(void) {
    Magic052Steps handlers = D_801EEC10;

    g_Scripts = BATTLE_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EEF84(void) {
    PartyMember* work;
    s32          cue;
    u8           timer;

    TASK(PartyMember)->unk_29 = 0;
    TASK(PartyMember)->unk_25 = 0x1D;
    TASK(PartyMember)->unk_26 = 0;
    TASK(PartyMember)->unk_24 = 0x84;
    TASK(PartyMember)->unk_27 = 0xB4;
    TASK(PartyMember)->unk_28 = 0;
    work                      = TASK(PartyMember);
    work->unk_2B              = 0;
    work->unk_2C.value        = 0;
    TASK(PartyMember)->unk_2A = 0;
    timer                     = TASK(PartyMember)->unk_09;
    if (timer != 0) {
        cue = 0x100;
        if (timer & 0x1) {
            cue = 0x101;
        }
    } else {
        cue = 0x102;
    }
    SND_SEQueueSelection(cue);
    Script_Select(5U);
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EF070(void) {
    PartyMember* work;

    if (Script_AnimStepLoop() != 0u) {
        work              = TASK(PartyMember);
        work->header.step = work->header.step + 1;
    } else {
        Area_AddActor();
    }
}

MATCH void func_801EF0C4(void) {
    Effect_Reset();
}
