#include "battle_03.h"

MATCH void func_801E483C(void) {
    volatile u8*          global;
    volatile PartyMember* work;

    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 4));
    global = (u8*)(PARTY_STATE_PTR);
    if (global[0x62EAu] != 0u) {
        Battle_PlayEnemySE(*(u16*)((*(u32*)(((u32)g_BattleCurrentEnemy + 0xE8u)) + 6u)));
    }
    GFX_PaletteFreeFadeTarget(TASK(void));
    GFX_PaletteAllocFade(TASK(void), 255, 255, 255, 0);
    work                         = TASK(PartyMember);
    work->unk_1C                 = -0x2000;
    work->unk_10                 = 0;
    ((PartyMember*)work)->unk_03 = 3;
}
