#include "magic039_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC94);

#include "overlays/bmagic/Effect_NextStepOnZeroTick.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH s32 func_801EEF3C(void) {
    u16* id;

    id = (u16*)&g_BattleActionId;
    switch (*id) {
        case 0x27:
        default:
            return 2;
        case 0xA3:
            return 3;
    }
}

MATCH void func_801EEF64(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

INCLUDE_ASM(func_801EEFA8);

MATCH void func_801EF070(void) {
    PartyBattler* src;

    src                = (PartyBattler*)D_801EB4E0;
    g_Task->coord_x_34 = src->coord_x_34;
    g_Task->coord_y_38 = src->coord_y_38;
    g_Task->word_3C    = src->word_3C;
    g_Task->unk_09     = 0;
    g_Task->timer      = 1;
    g_Task->step       = g_Task->step + 1;
}

MATCH void func_801EF0D4(void) {
    u8 temp_v1;

    temp_v1        = g_Task->unk_09 + 2;
    g_Task->unk_09 = temp_v1;
    if ((temp_v1 & 0xFF) == 0x10) {
        g_Task->timer = 0;
        g_Task->step += 1;
    }
}

MATCH void func_801EF134(void) {
    u8             temp_v0;
    PartyBattler** selected;

    g_Task->unk_09 += 1;
    temp_v0       = g_Task->timer + 2;
    g_Task->timer = temp_v0;
    if ((temp_v0 & 0xFF) == 0x18) {
        selected = &g_BattleSelectedActor;
        func_80196718(*selected);
        g_Task->unk_0B = func_8019651C(*selected, 0, 0, 0, 1);
        g_Task->step += 1;
    }
}

INCLUDE_ASM(func_801EF1F4);

INCLUDE_ASM(func_801EF320);

MATCH void func_801EF44C(void) {
    u8 temp_v0;

    g_Task->unk_09 += 1;
    temp_v0       = g_Task->timer - 2;
    g_Task->timer = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        func_80196718(g_BattleSelectedActor);
        func_800AF814(g_BattleTargetSelector);
        D_801EB4E0->unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF4E4(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC28;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->step);
    if (ACTOR_IN_USE(*g_Task) && g_Task->step != 0) {
        func_800AF764();
        func_801EF758();
    }
}

INCLUDE_ASM(func_801EF584);

MATCH void func_801EF690(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 16;
    g_Task->unk_09 = timer;
    if (timer == 128) {
        g_Task->step = g_Task->step + 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTimer.h"

INCLUDE_ASM(func_801EF758);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EFAA4);

INCLUDE_ASM(func_801F0054);
