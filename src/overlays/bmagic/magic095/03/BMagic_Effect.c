#include "magic095_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC18(void) {
    Callback handlers[5];

    __builtin_memcpy(handlers, D_801EEC04, sizeof(handlers));
    Effect_SetActorMatrix();
    SYS_DISPATCH_BYTE(handlers, g_Task->header.mode);
    PopMatrix();
}

INCLUDE_ASM(func_801EEC9C);

MATCH void func_801EEE60(void) {
    u32          slot;
    PartyMember* battler;
    s32          timer;

    func_801EFDDC();
    if (g_Task->timer == 12) {
        slot = LOBU(g_Battle.target_selector);
        if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
            battler = &g_Game.members[slot];
        } else {
            battler = (PartyMember*)(g_BattleEnemies + slot * BATTLE_ENEMY_STRIDE);
        }
        GFX_FreePaletteFadeTarget(battler);
        GFX_AllocPaletteFade(battler, 6, 4, 8, 0);
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x200);
    }
    timer         = g_Task->timer + 1;
    g_Task->timer = timer;
    if ((timer & BYTE_MASK) == 16) {
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
    if ((counter & BYTE_MASK) == 0x40) {
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
    u8           timer;
    u32          slot;
    u8*          selector;
    PartyMember* battler;

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
        if (!(counter & BYTE_MASK)) {
            g_Task->header.mode += 1;
        }
    }
}

MATCH void func_801F00D8(void) {
    u8 count;

    func_801F012C();
    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x20) {
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F012C);
