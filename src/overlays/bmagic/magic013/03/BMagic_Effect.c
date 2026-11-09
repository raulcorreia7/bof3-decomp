#include "magic013_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC14);

INCLUDE_ASM(func_801EED28);

#include "overlays/bmagic/Effect_Pause.h"

MATCH void func_801EEEA0(void) {
    u8*          selector;
    u32          slot;
    PartyMember* work;

    selector = (u8*)&g_Battle.target_selector;
    if (!(Battle_SlotIsBlocked(*selector) & BYTE_MASK) && (func_800AED5C(1, *selector) & BYTE_MASK)) {
        slot                               = Battle_AllocEffect(1, 0x48) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].unk_04       = 4;
        g_BattleEffects[slot].arg.unk_09   = 0x18;
        g_BattleEffects[slot].unk_0A       = 4;
        g_BattleEffects[slot].target.party = work;
        g_Task->param.unk_0B += 1;
    }
    g_Task->header.mode += 1;
}

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EEFD0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF014(void) {
    SYS_DISPATCH_BYTE(D_801F03C0, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_801EF4F0();
        func_801EF79C();
        PopMatrix();
        func_801EF648();
        func_801EFAA8();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF0A4);

#include "overlays/bmagic/Effect_CountUpWorkByteAndStep.h"

INCLUDE_ASM(func_801EF1F0);

/* hint: the step-limit select (0xC when the timer is 1, else 0x10) and the position adds leave the body 12 bytes over (0x124 against 0x118); first differing instruction: lw v0,56(a2) at +0x10 where retail holds y in another register. */
INCLUDE_ASM(func_801EF36C);

MATCH void func_801EF484(void) {
    PartyMember* work;
    PartyMember* active;

    work = g_Task;
    if (work->param.unk_0B == 0) {
        work->unk_04 = work->unk_04 - 1;
        if (work->unk_04 == 0) {
            active               = BATTLE_ACTIVE_WORK;
            active->param.unk_0B = active->param.unk_0B - 1;
            func_801E5988();
        }
    }
}

INCLUDE_ASM(func_801EF4F0);

INCLUDE_ASM(func_801EF648);

INCLUDE_ASM(func_801EF79C);

INCLUDE_ASM(func_801EFAA8);

MATCH void func_801EFDB4(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 7), 1, g_Task);
}

MATCH void func_801EFDF8(void) {
    SYS_DISPATCH_BYTE(D_801F03DC, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->unk_09 != 0) {
        func_801F00A8();
        func_801F0164();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EFE80);

/* hint: the sin/cos position offsets with the angle held in the scratchpad cell leave the body 4 bytes over (0x124 against 0x120); first differing instruction: sw ra,16(sp) at +0xC (retail saves a callee register first). */
INCLUDE_ASM(func_801EFF88);

MATCH void func_801F00A8(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = g_Task->unk_09 << 6;
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

INCLUDE_ASM(func_801F0164);

/* func_801F0358 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
