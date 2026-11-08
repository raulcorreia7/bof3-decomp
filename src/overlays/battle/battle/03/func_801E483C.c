#include "battle_03.h"

MATCH void func_801E483C(void) {
    volatile u8*          global;
    volatile PartyMember* work;

    SND_PlayCue(EMI_CUE_ID(2, 4));
    global = (u8*)(EFFECT_BANK_80140000);
    if (global[0x62EAu] != 0u) {
        func_801E52F0(*(u16*)((*(u32*)(((u32)g_BattleCurrentEnemy + 0xE8u)) + 6u)));
    }
    GFX_FreePaletteFadeTarget((void*)g_Task);
    GFX_AllocPaletteFade((void*)g_Task, 0xFF, 0xFF, 0xFF, 0);
    work                         = g_Task;
    work->unk_1C                 = -0x2000;
    work->unk_10                 = 0;
    ((PartyMember*)work)->unk_03 = 3;
}
