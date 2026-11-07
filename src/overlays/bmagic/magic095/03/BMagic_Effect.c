#include "magic095_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* blocker: a 0x14-byte constant block D_801EEC04 copied to the stack has no record type in this image; needs: type. */
INCLUDE_ASM(func_801EEC18);

INCLUDE_ASM(func_801EEC9C);

MATCH void func_801EEE60(void) {
    u32           slot;
    PartyBattler* battler;
    s32           timer;

    func_801EFDDC();
    if (g_Task->timer == 0xC) {
        slot = LOBU(g_BattleTargetSelector);
        if (slot < BATTLE_PARTY_SLOT_COUNT) {
            battler = &g_BattlePartyBattlers[slot];
        } else {
            battler = (PartyBattler*)(g_BattleEnemies + slot * BATTLE_ENEMY_STRIDE);
        }
        GFX_FreePaletteFadeTarget(battler);
        GFX_AllocPaletteFade(battler, 6, 4, 8, 0);
        func_800A9610(g_BattleTargetSelector, 0x200);
    }
    timer         = g_Task->timer + 1;
    g_Task->timer = timer;
    if ((timer & 0xFF) == 0x10) {
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEF64(void) {
    u8 counter;

    func_801EF1FC();
    func_801EF804();
    func_801EFDDC();
    counter        = g_Task->unk_09 + 1;
    g_Task->unk_09 = counter;
    if ((counter & 0xFF) == 0x40) {
        SND_QueueSelectionFx(0x101);
        SND_QueueSelectionFx(0x102);
        g_Task->unk_09 = 0x30;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEFFC(void) {
    u8 timer;

    func_801EF1FC();
    func_801EF804();
    func_801EFDDC();
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

MATCH void func_801EF070(void) {
    u8            timer;
    u32           slot;
    u8*           selector;
    PartyBattler* battler;

    func_801EFDDC();
    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (timer == 0) {
        BMAGIC_RELEASE_TARGET_AND_PLAY();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF1FC);

INCLUDE_ASM(func_801EF804);

INCLUDE_ASM(func_801EFDDC);

extern Callback D_801F0654[];

MATCH void func_801F0018(void) {
    Effect_SetActorMatrix();
    D_801F0654[g_Task->header.mode]();
    PopMatrix();
}

MATCH void func_801F0070(void) {
    u8 counter;

    if (BATTLE_ACTIVE_WORK->header.mode == 3) {
        counter        = g_Task->unk_09 - 1;
        g_Task->unk_09 = counter;
        if (!(counter & 0xFF)) {
            g_Task->header.mode += 1;
        }
    }
}

MATCH void func_801F00D8(void) {
    u8 temp_v1;

    func_801F012C();
    temp_v1        = g_Task->unk_09 + 1;
    g_Task->unk_09 = temp_v1;
    if ((temp_v1 & 0xFF) == 0x20) {
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F012C);
