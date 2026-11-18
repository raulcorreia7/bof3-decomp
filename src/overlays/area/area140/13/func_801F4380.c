#include "area140_13.h"

#ifdef NON_MATCHING
NON_MATCHING u8 func_801F4380(s32 x, s32 y) {
    s32 i;
    s32 base;
    s32 table_offset;
    u8  flag;
    u8  kind;
    u8  count;
    s32 j;
    u8  actor_slot;
    u16 limit_y;
    u16 limit_x;

    for (i = 0, table_offset = 0; i < 8; i++, table_offset += 6) {
        if ((u8)x == D_801F4A84[table_offset] && (u8)y == D_801F4A85[table_offset] && (D_801F4A86[table_offset] & 0xF) == g_Game.members[0].facing) {
            break;
        }
    }
    if (i == 8) {
        return 0;
    }
    base = i * 6;
    flag = D_801F4A87[base];
    if (SYS_TestFlag(g_SceneEventFlags, flag) != 0) {
        return 0;
    }
    kind = D_801F4A89[base];
    if (kind != 0) {
        count = D_80146254;
        if (count > 0) {
            limit_y = D_801F4AB6[kind * 2];
            limit_x = D_801F4AB4[kind * 2];
            for (j = 0; j < count; j++) {
                PartyMember* member;
                s32          product_x;
                s32          product_y;

                member    = &g_Game.members[j];
                product_x = member->unk_0C * member->unk_09;
                product_y = member->unk_10 * member->unk_09;
                if ((u16)(((member->pos.y.fixed + product_y) >> 16) - limit_y) >= 2) {
                    continue;
                }
                if ((u16)(((product_x + member->pos.x.fixed) >> 16) - limit_x) < 2) {
                    Game_SetScriptActive();
                    g_SceneEventMode = 0x29;
                    g_SceneEventStep = 0xA;
                    return 1;
                }
            }
        }
    }
    SYS_SetFlag(g_SceneEventFlags, flag);
    Area_SetCellPalette(D_801F4A84[base], D_801F4A85[base]);
    if (D_801F4A88[base] != 0) {
        actor_slot = Actor_FindFreeSpawned();
        if (actor_slot != 0xFF) {
            g_SpawnedActors[actor_slot].type         = 0x71;
            g_SpawnedActors[actor_slot].header.flags = 1;
            g_SpawnedActors[actor_slot].pos.x.fixed  = (u32)D_801F4A84[base] << 16;
            g_SpawnedActors[actor_slot].pos.y.fixed  = (u32)D_801F4A85[base] << 16;
            g_SpawnedActors[actor_slot].link         = flag;
        }
    }
    SND_PlaySE(EMI_SE_ID(SND_BANK_AREA, 4));
    return 1;
}
#else
INCLUDE_ASM(func_801F4380);
#endif
