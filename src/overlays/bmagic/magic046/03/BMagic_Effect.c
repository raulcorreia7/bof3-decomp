#include "magic046_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC28);

INCLUDE_ASM(func_801EED28);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEF70(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

MATCH void func_801EEFB4(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC00.steps;
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_SpadWork);
}

INCLUDE_ASM(func_801EF014);

INCLUDE_ASM(func_801EF090);

#include "overlays/bmagic/Effect_TickOnZeroTick.h"

#include "../../Effect_DispatchHandlerSlot2.h"

MATCH void func_801EF250(void) {
    g_SpadWork                              = D_801EB4E0;
    BATTLE_ACTIVE_WORK->word_08.byte.unk_0B = 0;
    g_SpadWork->word_08.byte.unk_09         = 0;
    Actor_SelectScript(2U);
    g_SpadWork->step_01 = 1;
    g_SpadWork->unk_02  = 1;
}

#include "overlays/bmagic/Effect_AddActorStepOnPlaying.h"

MATCH void func_801EF304(void) {
    func_801E5988();
}

MATCH void func_801EF324(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC1C;
    SYS_DISPATCH_BYTE(handlers.handlers, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0) {
        func_801EFB90();
        func_801EFC48();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF3B8);

MATCH void func_801EF540(void) {
    s32 temp_a0;
    s32 temp_v0;
    u8  temp_v0_2;

    temp_v0            = (g_SpadWork->word_08.byte.unk_09 + g_SpadWork->word_08.byte.unk_0B) & 0x3F;
    SP_REF(s16, 2)     = (s16)(temp_v0 << 6);
    temp_a0            = g_SpadWork->unk_14 + ((s32)(rsin((s16)(temp_v0 << 6)) * 0x12C) >> 0xC);
    g_SpadWork->unk_0C = temp_a0;
    g_SpadWork->coord_x_34.raw += (s32)(rsin(temp_a0) * 0x7000) >> 0xC;
    g_SpadWork->coord_y_38.raw += (s32)(rcos(g_SpadWork->unk_0C) * 0x7000) >> 0xC;
    func_800AF764(g_SpadWork);
    func_801EF7E8();
    temp_v0_2                       = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0_2;
    if ((temp_v0_2 & 0xFF) == 0x10) {
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF660(void) {
    s32 temp_a0;
    s32 temp_v0;
    u8  temp_v0_2;

    temp_v0            = (g_SpadWork->word_08.byte.unk_09 + g_SpadWork->word_08.byte.unk_0B) & 0x3F;
    SP_REF(s16, 2)     = (s16)(temp_v0 << 6);
    temp_a0            = g_SpadWork->unk_14 + ((s32)(rsin((s16)(temp_v0 << 6)) * 0x12C) >> 0xC);
    g_SpadWork->unk_0C = temp_a0;
    g_SpadWork->coord_x_34.raw += (s32)(rsin(temp_a0) * 0x7000) >> 0xC;
    g_SpadWork->coord_y_38.raw += (s32)(rcos(g_SpadWork->unk_0C) * 0x7000) >> 0xC;
    func_800AF764(g_SpadWork);
    func_801EF7E8();
    g_SpadWork->word_08.byte.unk_09 += 1;
    temp_v0_2                         = g_SpadWork->word_08.byte.timer_0A - 1;
    g_SpadWork->word_08.byte.timer_0A = temp_v0_2;
    if (!(temp_v0_2 & 0xFF)) {
        D_801EB4E0->word_08.byte.unk_0B -= 1;
        g_SpadWork->flags_00 = 0;
        g_SpadWork->step_01  = 0;
        g_SpadWork->unk_02   = 0;
        g_SpadWork->unk_03   = 0;
        g_SpadWork->unk_04   = 0;
    }
}

INCLUDE_ASM(func_801EF7E8);

MATCH void func_801EFB90(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vz = 0;
    rot.vy = 0;
    rot.vx = 0;
    BMAGIC_PROJECT_ACTOR_MATRIX(BATTLE_ACTIVE_WORK);
}

INCLUDE_ASM(func_801EFC48);

/* func_801EFED0 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
