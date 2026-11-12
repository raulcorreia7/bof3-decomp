#include "magic043_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC18(void) {
    Magic043Steps handlers;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (BMAGIC_EFFECT_SLOTS[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&BMAGIC_EFFECT_SLOTS[i];
            g_BattleEffectBattler = BMAGIC_EFFECT_SLOTS[i].target.party;
            BMagic_DispatchEffectMode();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

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

MATCH void func_801EEF98(void) {
    u8 count;

    g_PaletteFades[g_Task->timer].offset.red += 2;
    g_PaletteFades[g_Task->timer].offset.green += 2;
    g_PaletteFades[g_Task->timer].offset.blue += 2;
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        g_Task->unk_09 = 4;
        g_Task->header.mode += 1;
    }
}

INCLUDE_ASM(func_801EF0B4);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EF360 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF3A4(void) {
    SYS_DISPATCH_BYTE(D_801EFC8C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF72C();
        func_801EF7F8();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF42C);

MATCH void func_801EF55C(void) {
    g_Task->pos.x.fixed += g_Task->unk_0C;
    g_Task->pos.y.fixed += g_Task->unk_10;
    g_Task->unk_09 += 1;
    g_Task->timer += 2;
    if (g_Task->timer == 0x10) {
        g_Task->header.step += 1;
    }
}

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

MATCH void func_801EF64C(void) {
    g_Task->pos.x.fixed += g_Task->unk_0C;
    g_Task->pos.y.fixed += g_Task->unk_10;
    g_Task->unk_09 += 1;
    g_Task->timer -= 2;
    if (g_Task->timer == 0) {
        BMAGIC_TICK_EFFECT_WORK();
        BMagic_ResetLocalWork();
    }
}

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
