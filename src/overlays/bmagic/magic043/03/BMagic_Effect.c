#include "magic043_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC18);

INCLUDE_ASM(func_801EED30);

MATCH void func_801EEEF0(void) {
    PartyMember* battler;
    u8           value;

    battler        = g_Battle.selected_actor;
    value          = g_Task->unk_09 - 1;
    g_Task->unk_09 = value;
    if (!(value & BYTE_MASK)) {
        GFX_FreePaletteFadeTarget(battler);
        g_Task->timer  = GFX_AllocPaletteFade(battler, 0, 0, 0, 1);
        g_Task->unk_09 = 4;
        g_Task->header.mode += 1;
    }
}

INCLUDE_ASM(func_801EEF98);

INCLUDE_ASM(func_801EF0B4);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EF360 */
MATCH void BMagic_DispatchMode(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EF3A4(void) {
    SYS_DISPATCH_BYTE(D_801EFC8C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF72C();
        func_801EF7F8();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF42C);

/* blocker: candidate loads g_Task into v1 where retail uses v0, and the body is 8 bytes shorter; first diff: lui v1 against v0 at 0x801EF55C. */
INCLUDE_ASM(func_801EF55C);

MATCH void func_801EF5E0(void) {
    PartyMember* work;
    u8           count;

    work         = g_Task;
    count        = work->unk_09 + 1;
    work->unk_09 = count;
    work->pos.x.fixed += work->unk_0C;
    work->pos.y.fixed += work->unk_10;
    if (count == 24) {
        g_Task->header.step++;
    }
}

INCLUDE_ASM(func_801EF64C);

MATCH void func_801EF72C(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0x400;
    rot.vy = D_801EFC9C[g_Task->facing];
    rot.vz = 0;
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

INCLUDE_ASM(func_801EF7F8);

/* func_801EFC24 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
