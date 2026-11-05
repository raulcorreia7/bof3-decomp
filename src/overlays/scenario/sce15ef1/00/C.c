#include "sce15ef1_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801D0C0C(void) {
    /* FAKE: retail reads the handler record from entry $v0; the pin is the
       entry-register residual (identical bytes to the unpinned 84.46%). */
    MATCH_REG(u8*, entity, "v0");

    D_801D3918[entity[1]]();
}

INCLUDE_ASM(func_801D0C48);

MATCH void func_801D0CC0(void) {
    u16 screen_x;
    u8  mode;

    screen_x           = g_SpadWork->unk_2E + 0x20;
    g_SpadWork->unk_2E = screen_x;
    func_801D147C(&g_SpadWork->unk_64, (s16)screen_x, 6);
    mode               = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = mode;
    if (!(mode & 0xFF)) {
        g_SpadWork->unk_09 = 0x40;
        g_SpadWork->unk_01 += 1;
    }
}

MATCH void func_801D0D54(void) {
    u8 mode;

    func_801D147C(&g_SpadWork->unk_64, (s16)g_SpadWork->unk_2E, 6);
    mode               = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = mode;
    if (!(mode & 0xFF)) {
        g_SpadWork->unk_09 = 0x20;
        g_SpadWork->unk_01 += 1;
    }
}

INCLUDE_ASM(func_801D0DD8);

INCLUDE_ASM(func_801D0F10);

INCLUDE_ASM(func_801D0FEC);

INCLUDE_ASM(func_801D106C);

INCLUDE_ASM(func_801D12A0);

MATCH void func_801D13F4(void) {
    u8 remaining;

    g_SpadWork->unk_2E -= 0x10;
    g_SpadWork->unk_03 -= 8;
    func_801D1A60();
    func_801D1678(&g_SpadWork->unk_18, &g_SpadWork->x, g_SpadWork->unk_03);
    remaining          = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = remaining;
    if (!(remaining & 0xFF)) {
        func_80196070();
    }
}

INCLUDE_ASM(func_801D147C);

INCLUDE_ASM(func_801D1678);

MATCH void func_801D199C(void) {
    u8          i;
    EffectSlot* slot;

    slot = D_801D39A8;
    for (i = 0; i < EFFECT_SLOT_COUNT; i++, slot++) {
        slot->active = 0;
    }
}

MATCH void func_801D19C8(void) {
    u8          i;
    EffectSlot* slot;
    Actor*      actor;

    slot = D_801D39A8;
    for (i = 0; i < EFFECT_SLOT_COUNT; slot++, i++) {
        if (slot->active == 0) {
            slot->active = 1;
            slot->unk_01 = 0;
            slot->life   = 0x10;
            actor        = g_SpadWork;
            slot->x      = actor->x.fixed;
            slot->y      = actor->y.fixed;
            slot->z      = actor->z.fixed;
            slot->size   = 0x100;
            slot->unk_16 = 0x60;
            slot->unk_17 = 0;
            return;
        }
    }
}

MATCH s32 func_801D1A60(void) {
    MATRIX      matrix;
    u8          i;
    s32         alive;
    EffectSlot* slot;

    alive = 0;
    Area_SetCameraMatrix(&matrix);
    slot = D_801D39A8;
    for (i = 0; i < EFFECT_SLOT_COUNT; slot++, i++) {
        if (slot->active != 0) {
            alive = 1;
            slot->size -= 0x10;
            if (--slot->life == 0) {
                slot->active = 0;
            }
            func_801D1B10(slot);
        }
    }
    return alive;
}

INCLUDE_ASM(func_801D1B10);

INCLUDE_ASM(func_801D1CD4);

#include "shared/Area_InitSpin.h"

INCLUDE_ASM(func_801D2088);

MATCH void func_801D2138(s32* first, s32* second) {
    s32 folded;
    s32 swapped;

    folded  = *first ^ *second;
    *first  = folded;
    swapped = *second ^ folded;
    *second = swapped;
    *first ^= swapped;
}

MATCH void func_801D2170(void) {
    SYS_DISPATCH_TASK(D_801D3954, 1, g_SpadWork);
}

INCLUDE_ASM(func_801D21B4);

INCLUDE_ASM(func_801D23A0);

INCLUDE_ASM(func_801D2474);

INCLUDE_ASM(func_801D26BC);

INCLUDE_ASM(func_801D2934);

MATCH void func_801D2B44(void) {
    Actor_Clear();
}

MATCH void func_801D2B64(void) {
    SYS_DISPATCH_TASK(D_801D396C, 1, g_SpadWork);
}

/* Tried: spad body (five work stores, unk_01++, SND_PlayCue(520)), with
 * direct and local-pointer variants. GCC reloads the work pointer into
 * v0 and hoists the lbu before the zero stores; retail reloads into a0
 * and keeps the first copy for the stores. First diff +0x08: lui v0,0x1f80.
 */
INCLUDE_ASM(func_801D2BA8);

INCLUDE_ASM(func_801D2C00);

INCLUDE_ASM(func_801D2C94);

/* nonmatching: step of the actor position (func_801D36BC(&x, unk_0C, unk_10)), then unk_0C += unk_18, unk_10 += unk_1C, unk_09--, unk_18 -= 0x100, unk_1C -= 0x200, Actor_Clear at zero. Three statement orders tried; best differs from retail at +0x2C (retail loads lbu a1,9(v1) first, candidate lw v0,12(v1)). */
INCLUDE_ASM(func_801D2D5C);

MATCH void func_801D2DEC(void) {
    SYS_DISPATCH_TASK(D_801D397C, 1, g_SpadWork);
}

INCLUDE_ASM(func_801D2E30);

INCLUDE_ASM(func_801D2FD8);

INCLUDE_ASM(func_801D30AC);

INCLUDE_ASM(func_801D32F4);

INCLUDE_ASM(func_801D34F0);

MATCH void func_801D369C(void) {
    Actor_Clear();
}

INCLUDE_ASM(func_801D36BC);
