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

    GFX_ADD_LAYER_DRAW_MODE(3, GetTPage(0, 0, 0x3C0, 0));
    i = 0;
    do {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        setRGB0(prim, 0xFF, 0xFF, 0xFF);

        prim->r1 = *(volatile u8*)(D_800C2640 + ((*(EnemyBattler* volatile*)&g_BattleCurrentEnemy)->unk_F0 - 8) * 3);
        next     = (i + 1) & 0x1F;
        prim->g1 = *(volatile u8*)(D_800C2641 + ((*(EnemyBattler* volatile*)&g_BattleCurrentEnemy)->unk_F0 - 8) * 3);
        prim->b1 = *(volatile u8*)(D_800C2642 + ((*(EnemyBattler* volatile*)&g_BattleCurrentEnemy)->unk_F0 - 8) * 3);
        setRGB2(prim, *(volatile u8*)(D_800C2640 + ((*(EnemyBattler* volatile*)&g_BattleCurrentEnemy)->unk_F0 - 8) * 3),
                *(volatile u8*)(D_800C2641 + ((*(EnemyBattler* volatile*)&g_BattleCurrentEnemy)->unk_F0 - 8) * 3),
                *(volatile u8*)(D_800C2642 + ((*(EnemyBattler* volatile*)&g_BattleCurrentEnemy)->unk_F0 - 8) * 3));

        enemy = (EnemyBattler*)g_Task;
        setXY3(prim, enemy->screen_x, enemy->screen_y, enemy->screen_x + ring[i][0], enemy->screen_y + ring[i][1], enemy->screen_x + ring[next][0], enemy->screen_y + ring[next][1]);
        SetSemiTrans(prim, 1);
        GFX_AddPrim(3, sizeof(POLY_G3));
        i++;
    } while (i < 64);
}
#else
INCLUDE_ASM(func_800C236C);
#endif
