#include "magic100_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC70);

MATCH void func_801EED9C(void) {
    if (g_Task->unk_09 != 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEE58 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEE9C(void) {
    SYS_DISPATCH_BYTE(D_801EFDD0, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF434();
        func_801EF4E8();
        PopMatrix();
        func_801EF8E8();
        func_801EF9D4();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EEF3C);

MATCH void func_801EF0D8(void) {
    u32          slot;
    PartyMember* battler;
    u8           timer;

    slot = LOBU(g_Battle.target_selector);
    if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
        battler = &g_Game.members[slot];
    } else {
        battler = (PartyMember*)(g_BattleEnemies + slot * BATTLE_ENEMY_STRIDE);
    }
    if (g_Task->param.unk_0B & 0x1) {
        g_Task->unk_20 = (g_Task->unk_20 + 0x200) & 0xFFF;
    } else {
        g_Task->unk_20 = (g_Task->unk_20 - 0x200) & 0xFFF;
    }
    g_Task->unk_14 = func_800AF4A0(battler, 0xC000, g_Task->unk_18 << 6);
    timer          = g_Task->timer + 4;
    g_Task->timer  = timer;
    if (timer == 16) {
        g_Task->header.step++;
    }
}

INCLUDE_ASM(func_801EF1DC);

INCLUDE_ASM(func_801EF358);

MATCH void func_801EF434(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    ;
    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = 0;
    pos.vx = (g_Task->pos.x.fixed >> 9) - 0x4000;
    pos.vy = (g_Task->pos.y.fixed >> 9) - 0x4000;
    pos.vz = -(COORD_INT(g_Task->pos.z) + 0x100) / 2;
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}

INCLUDE_ASM(func_801EF4E8);

MATCH void func_801EF8E8(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = 0;
    pos.vx = (g_Task->pos.x.fixed >> 9) - 0x4000;
    pos.vy = (g_Task->pos.y.fixed >> 9) - 0x4000;
    if (g_Task->header.step < 3) {
        pos.vz = -COORD_INT(g_Task->pos.z) / 2;
    } else {
        pos.vz = -(s16)Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed) / 2;
    }
    RotTransMatrix(&pos, matrix, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2(&g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

INCLUDE_ASM(func_801EF9D4);
