#include "boss008_16.h"

#ifdef NON_MATCHING
NON_MATCHING void func_800C236C(u8 phase) {
    s32           ring[64][2];
    EnemyBattler* enemy;
    POLY_G3*      prim;
    u8            i;
    u8            next;

    i = 0;
    do {
        ring[i][0] = FIXED_MUL(rsin(i << 7), phase);
        ring[i][1] = FIXED_MUL(rcos(i << 7), phase);
        i++;
    } while (i < 64);

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 0, 0x3C0, 0), 0);
    GFX_AddPrim(3, sizeof(DR_MODE));
    i = 0;
    do {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        prim->r0 = 0xFF;
        prim->g0 = 0xFF;
        prim->b0 = 0xFF;

        prim->r1 = *(volatile u8*)(D_800C2640 + ((*(EnemyBattler* volatile*)&g_BattleCurrentEnemy)->unk_F0 - 8) * 3);
        next     = (i + 1) & 0x1F;
        prim->g1 = *(volatile u8*)(D_800C2641 + ((*(EnemyBattler* volatile*)&g_BattleCurrentEnemy)->unk_F0 - 8) * 3);
        prim->b1 = *(volatile u8*)(D_800C2642 + ((*(EnemyBattler* volatile*)&g_BattleCurrentEnemy)->unk_F0 - 8) * 3);
        prim->r2 = *(volatile u8*)(D_800C2640 + ((*(EnemyBattler* volatile*)&g_BattleCurrentEnemy)->unk_F0 - 8) * 3);
        prim->g2 = *(volatile u8*)(D_800C2641 + ((*(EnemyBattler* volatile*)&g_BattleCurrentEnemy)->unk_F0 - 8) * 3);
        prim->b2 = *(volatile u8*)(D_800C2642 + ((*(EnemyBattler* volatile*)&g_BattleCurrentEnemy)->unk_F0 - 8) * 3);

        enemy    = (EnemyBattler*)g_Task;
        prim->x0 = enemy->unk_2E;
        prim->y0 = enemy->unk_30;
        prim->x1 = enemy->unk_2E + ring[i][0];
        prim->y1 = enemy->unk_30 + ring[i][1];
        prim->x2 = enemy->unk_2E + ring[next][0];
        prim->y2 = enemy->unk_30 + ring[next][1];
        SetSemiTrans(prim, 1);
        GFX_AddPrim(3, sizeof(POLY_G3));
        i++;
    } while (i < 64);
}
#else
INCLUDE_ASM(func_800C236C);
#endif
