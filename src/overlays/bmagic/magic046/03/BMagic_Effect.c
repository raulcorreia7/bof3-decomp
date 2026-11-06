#include "magic046_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC28);

INCLUDE_ASM(func_801EED28);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEF70(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->header.mode);
}

MATCH void func_801EEFB4(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC00.steps;
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_Task);
}

MATCH void func_801EF014(void) {
    PartyBattler* work;
    PartyBattler* actor;
    s32           z;

    g_Task->facing    = D_801EB4E0->facing;
    work              = g_Task;
    actor             = D_801EB4E0;
    work->pos.x.fixed = actor->pos.x.fixed;
    work->pos.y.fixed = actor->pos.y.fixed;
    z                 = actor->pos.z.fixed;
    work->unk_0B      = 0;
    work->pos.z.fixed = z;
    g_Task->unk_09    = 0;
    g_Task->header.step += 1;
}

INCLUDE_ASM(func_801EF090);

#include "overlays/bmagic/Effect_TickOnZeroTick.h"

#include "../../Effect_DispatchHandlerSlot2.h"

MATCH void func_801EF250(void) {
    g_Task                     = D_801EB4E0;
    BATTLE_ACTIVE_WORK->unk_0B = 0;
    g_Task->unk_09             = 0;
    Actor_SelectScript(2U);
    g_Task->header.mode = 1;
    g_Task->header.step = 1;
}

#include "overlays/bmagic/Effect_AddActorStepOnPlaying.h"

MATCH void func_801EF304(void) {
    func_801E5988();
}

MATCH void func_801EF324(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC1C;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->header.step);
    if (g_Task->header.flags != 0) {
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

    temp_v0        = (g_Task->unk_09 + g_Task->unk_0B) & 0x3F;
    SP_REF(s16, 2) = (temp_v0 << 6);
    temp_a0        = g_Task->unk_14 + ((rsin((s16)(temp_v0 << 6)) * 0x12C) >> 0xC);
    g_Task->unk_0C = temp_a0;
    g_Task->pos.x.fixed += (rsin(temp_a0) * 0x7000) >> 0xC;
    g_Task->pos.y.fixed += (rcos(g_Task->unk_0C) * 0x7000) >> 0xC;
    func_800AF764(g_Task);
    func_801EF7E8();
    temp_v0_2      = g_Task->unk_09 + 1;
    g_Task->unk_09 = temp_v0_2;
    if ((temp_v0_2 & 0xFF) == 0x10) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF660(void) {
    s32 temp_a0;
    s32 temp_v0;
    u8  temp_v0_2;

    temp_v0        = (g_Task->unk_09 + g_Task->unk_0B) & 0x3F;
    SP_REF(s16, 2) = (temp_v0 << 6);
    temp_a0        = g_Task->unk_14 + ((rsin((s16)(temp_v0 << 6)) * 0x12C) >> 0xC);
    g_Task->unk_0C = temp_a0;
    g_Task->pos.x.fixed += (rsin(temp_a0) * 0x7000) >> 0xC;
    g_Task->pos.y.fixed += (rcos(g_Task->unk_0C) * 0x7000) >> 0xC;
    func_800AF764(g_Task);
    func_801EF7E8();
    g_Task->unk_09 += 1;
    temp_v0_2     = g_Task->timer - 1;
    g_Task->timer = temp_v0_2;
    if (!(temp_v0_2 & 0xFF)) {
        D_801EB4E0->unk_0B -= 1;
        g_Task->header.flags = 0;
        g_Task->header.mode  = 0;
        g_Task->header.step  = 0;
        g_Task->unk_03       = 0;
        g_Task->unk_04       = 0;
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
